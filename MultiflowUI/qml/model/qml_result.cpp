//
// Created by miku on 11/9/2023.
//

#include "qml_result.hpp"

QmlResult QmlResult::success(ml::Number value) {
    return QmlResult({}, true, value);
}

QmlResult QmlResult::failure(QString message) {
    return QmlResult(std::move(message), false, static_cast<ml::Number>(0));
}

QmlResult::QmlResult(QString message, bool success, ml::Number value)
    : _message(std::move(message)), _success(success), _value(value) {

}

const QString& QmlResult::message() const {
    return _message;
}

bool QmlResult::success() const {
    return _success;
}

ml::Number QmlResult::value() const {
    return _value;
}
