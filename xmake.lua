add_rules("mode.release", "mode.debug")
set_languages("c99", "cxx20")
set_xmakever("2.9.9")
add_requires("gtest")

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
        add_files("src/*.c")
    end)
end

-- for test
target("test-lib")
    set_kind("object")
    set_default(false)
    add_files("test/test-lib.cpp")

for _, file in ipairs(os.files("test/*.cpp")) do
    local name = path.basename(file)
    if name ~= "test-lib" then
        target(name, function()
            set_kind("binary")
            set_policy("build.sanitizer.address", true)
            set_policy("build.sanitizer.leak", true)
            set_policy("build.sanitizer.undefined", true)
            set_default(false)
            add_includedirs("src")
            add_packages("gtest")
            add_links("gtest_main")
            add_files("test/"..name..".cpp")
            add_deps("ez-string-object", "test-lib")
            add_tests("test", {realtime_output = true})
        end)
    end
end
