//
// Created by Hatsune Miku on 2023-11-26.
//

#include "PvtCalculationUnit.hpp"

#include <logging/logging.hpp>
#include <math/math.hpp>

using ml::Number;

PvtCalculationUnit::PvtCalculationUnit(QObject* parent)
    : AbstractCalculationUnit(parent) {
}

QVector<Number> PvtCalculationUnit::evaluateOne(
    const Number pressure, const Number temperature, const QMap<QString, QVariant>& row) const {
    ml::Environment env{
        {"T", temperature},
        {"Tr", temperature},
        {"P", pressure},
        {"y0", row["原油相对密度"].toString().toDouble()},
        {"yg", row["天然气相对密度"].toString().toDouble()},
        {"rho-w", row["水相对密度"].toString().toDouble()},
        {"fw", row["实际含水率"].toString().toDouble()},
        {"Rsb", row["饱和溶解油气比"].toString().toDouble()},
    };
    const auto* service = FormulaService::getInstance();

    const QString dissolvedGasOilRatioModel = _helper["溶解油气比模型"].value.toString();
    const QString oilSaturatedPressureModel = _helper["原油饱和压力模型"].value.toString();
    const QString oilVolumeCoefficientModel = _helper["原油体积系数模型"].value.toString();
    const QString groundGasOilViscosityModel = _helper["地面脱气原油粘度模型"].value.toString();
    const QString saturatedOilViscosityModel = _helper["饱和原油粘度模型"].value.toString();
    const QString unsaturatedOilViscosityModel = _helper["未饱和原油粘度模型"].value.toString();
    const QString truncatedWaterRatioModel = _helper["截断含水率模型"].value.toString();
    const QString gasViscosityModel = _helper["气体粘度模型"].value.toString();
    const QString oilWaterMixtureViscosityModel = _helper["油水混合物粘度模型"].value.toString();

    // 要死了，这也太多了吧

    // 好！先算溶解油气比！
    Number Rs;
    if (dissolvedGasOilRatioModel == "Standing") {
        Rs = service->formula("dissolve-gf-ratio-standing")
            .expression()->evaluate(env);
    }
    else if (dissolvedGasOilRatioModel == "Vasquez-Beggs") {
        Rs = service->formula("dissolve-gf-vasquez-beggs")
            .expression()->evaluate(env);
    }
    else if (dissolvedGasOilRatioModel == "Glaso") {
        Rs = service->formula("dissolve-gf-glaso")
            .expression()->evaluate(env);
    }
    else {
        emit onError("溶解油气比模型未知");
        return {};
    }
    log_info("Rs = {}", Rs);
    env.set("Rs", Rs);

    // 很好！再算原油饱和压力！
    Number pb;
    if (oilSaturatedPressureModel == "Standing") {
        pb = service->formula("oil-standing")
            .expression()->evaluate(env);
    }
    else if (oilSaturatedPressureModel == "Lasater") {
        pb = service->formula("oil-lasater")
            .expression()->evaluate(env);
    }
    else if (oilSaturatedPressureModel == "Vasquez-Beggs") {
        pb = service->formula("oil-vasquez-beggs")
            .expression()->evaluate(env);
    }
    else {
        emit onError("原油饱和压力模型未知");
        return {};
    }
    log_info("pb = {}", pb);
    env.set("pb", pb);

    // 来吧！原油体积系数！
    Number b0b;
    if (oilVolumeCoefficientModel == "Standing") {
        b0b = service->formula("oil-volume-coefficient-standing")
            .expression()->evaluate(env);
    }
    else if (oilVolumeCoefficientModel == "Vasquez-Beggs") {
        b0b = service->formula("oil-volume-coefficient-vb")
            .expression()->evaluate(env);
    }
    else {
        emit onError("原油体积系数模型未知");
        return {};
    }
    log_info("b0b = {}", b0b);
    env.set("b0b", b0b);

    // 面对我！地面脱气原油粘度！
    Number miuOd;
    if (groundGasOilViscosityModel == "Beggs-Robinson") {
        miuOd = service->formula("ground-miu-od-beggs-robinson")
            .expression()->evaluate(env);
    }
    else if (groundGasOilViscosityModel == "Glaso") {
        miuOd = service->formula("ground-miu-od-glaso")
            .expression()->evaluate(env);
    }
    else {
        emit onError("地面脱气原油粘度模型未知");
        return {};
    }
    log_info("miuOd = {}", miuOd);
    env.set("miu-od", miuOd);

    // 就是你了！饱和原油粘度！
    Number miu0;
    if (saturatedOilViscosityModel == "Beggs-Robinson") {
        miu0 = service->formula("saturated-oil-beggs-robinson")
            .expression()->evaluate(env);
    }
    else if (saturatedOilViscosityModel == "Hossain et al.") {
        miu0 = service->formula("saturated-oil-hossian-etal")
            .expression()->evaluate(env);
    }
    else {
        emit onError("饱和原油粘度模型未知");
        return {};
    }
    log_info("miu0 = {}", miu0);
    env.set("miu-0", miu0);

    // 你也别跑！未饱和原油粘度！
    Number miuU;
    if (unsaturatedOilViscosityModel == "Vasquez-Beggs") {
        miuU = service->formula("unsaturated-oil-vasquez-beggs")
            .expression()->evaluate(env);
    }
    else if (unsaturatedOilViscosityModel == "Kartoatmodjo-Schmidt") {
        miuU = service->formula("unsaturated-oil-kartoatmodjo-schmidt")
            .expression()->evaluate(env);
    }
    else {
        emit onError("未饱和原油粘度模型未知");
        return {};
    }
    log_info("miuU = {}", miuU);
    env.set("miu-u", miuU);

    // 终于来了！原油密度！
    const Number rho0 = service->formula("oil-density")
        .expression()->evaluate(env);
    log_info("rho0 = {}", rho0);
    env.set("rho-0", rho0);

    // 没想到吧！水粘度！
    const Number miuw = service->formula("water-viscosity")
        .expression()->evaluate(env);
    log_info("miuw = {}", miuw);
    env.set("miu-w", miuw);

    // 看到你了！截断含水率！
    Number fw0;
    if (truncatedWaterRatioModel == "给定值") {
        fw0 = row["截断含水率"].toString().toDouble();
    }
    else if (truncatedWaterRatioModel == "Brauner-Ullmann") {
        fw0 = service->formula("truncated-water-ratio-brauner-ullmann")
            .expression()->evaluate(env);
    }
    else {
        emit onError("截断含水率模型未知");
        return {};
    }
    log_info("fw0 = {}", fw0);
    env.set("fw0", fw0);

    // 哈哈！油水混合物粘度！
    Number mium;
    if (oilWaterMixtureViscosityModel == "反转法") {
        env.set("wv", miuw);
        env.set("fv", miu0);
        mium = service->formula("oil-water-mixture-viscosity-reverse-method")
            .expression()->evaluate(env);
    }
    else if (oilWaterMixtureViscosityModel == "体积比法") {
        mium = service->formula("oil-water-mixture-viscosity-volume-ratio")
            .expression()->evaluate(env);
    }
    else if (oilWaterMixtureViscosityModel == "Woelflin") {
        mium = service->formula("oil-water-mixture-viscosity-woelflin")
            .expression()->evaluate(env);
    }
    else if (oilWaterMixtureViscosityModel == "Brinkman") {
        mium = service->formula("oil-water-mixture-viscosity-brinkman")
            .expression()->evaluate(env);
    }
    else {
        emit onError("油水混合物粘度模型未知");
        return {};
    }
    log_info("mium = {}", mium);
    env.set("miu-m", mium);

    // 最后一个！气体粘度！
    Number miug;
    if (gasViscosityModel == "Lee et al.") {
        miug = service->formula("gas-viscosity-lee-etal")
            .expression()->evaluate(env);
    }
    else {
        emit onError("气体粘度模型未知");
        return {};
    }

    return {
        /* 饱和压力 */ pb,
        /* 溶解油气比 */ Rs,
        /* 原油体积系数 */ b0b,
        /* 地面脱气原油粘度 */ miuOd,
        /* 饱和原油粘度 */ miu0,
        /* 未饱和原油粘度 */ miuU,
        /* 气体粘度 */ miug,
        /* 水粘度 */ miuw,
        /* 油水混合物粘度 */ mium,
        /* 原油密度 */ rho0
    };
}

QVector<QVector<QVector<Number>>> PvtCalculationUnit::evaluate(const QString& category) const {
    const auto variables = _independentVariables->get(category);

    if (variables.size() != 1) {
        emit onError("PVT计算单元只能有一组输入数据");
        return {};
    }

    Number pressureStart;
    Number pressureEnd;
    Number temperatureStart;
    Number temperatureEnd;

    if (_helper["压力类型"].value.toString() == "单一值") {
        pressureStart = _helper["压力定值"].value.toDouble();
        pressureEnd = pressureStart;
    }
    else {
        pressureStart = _helper["压力范围起始"].value.toDouble();
        pressureEnd = _helper["压力范围终止"].value.toDouble();
    }

    if (_helper["温度类型"].value.toString() == "单一值") {
        temperatureStart = _helper["温度定值"].value.toDouble();
        temperatureEnd = temperatureStart;
    }
    else {
        temperatureStart =_helper["温度范围起始"].value.toDouble();
        temperatureEnd = _helper["温度范围终止"].value.toDouble();
    }

    QVector<QVector<QVector<Number>>> ret{};

    // 要命了
    // NOLINTNEXTLINE
    for (Number pressure = pressureStart; pressure <= pressureEnd; ++pressure) {
        QVector<QVector<Number>> variableSet{};

        // NOLINTNEXTLINE
        for (Number temperature = temperatureStart; temperature <= temperatureEnd; ++temperature) {
            try {
                variableSet.append(evaluateOne(pressure, temperature, variables.first()));
            }
            catch (const std::exception& e) {
                emit onError(e.what());
                return ret;
            }
        }
        log_info("variableSet = {}", variableSet.size());
        ret.append(variableSet);
    }
    return ret;
}
