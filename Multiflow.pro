TEMPLATE = subdirs

message("MULTIFLOW BUILDING STARTED")

debug {
    message("BUILD TYPE: DEBUG")
} else {
    message("BUILD TYPE: RELEASE")
}

SUBDIRS = MultiflowUI MultiflowLibrary
MultiflowUI.depends = MultiflowLibrary
