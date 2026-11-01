add_rules("mode.release", "mode.debug")
set_languages("c99")
set_xmakever("2.9.9")

includes("@builtin/xpack")

-- project metadata
set_project("ez-string-lib")
set_version("0.0.1")
set_license("MIT")

for _, kind in pairs({"static", "shared", "object"}) do
    target("ez-string-"..kind, function()
        set_kind(kind)
        set_basename("ez-string")
        if kind == "static" or kind == "shared" then
            set_default(true)
        else
            set_default(false)
        end
        add_files("*.c")
    end)
end
