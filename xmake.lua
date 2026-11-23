add_rules("mode.release", "mode.debug")
set_languages("c99", "cxx20")
set_xmakever("2.9.9")
add_requires("gtest")

includes("@builtin/xpack")

-- project metadata
set_project("ez-string-lib")
set_version("0.0.1")
set_license("MIT")

local sanitizers = {
    asan = "address",
    ubsan = "undefined",
    lsan = "leak",
    msan = "memory"
}

for short_san, long_san in pairs(sanitizers) do 
    option(short_san, function () 
        set_default(false)
        set_description("Enable "..long_san.." sanitizer")
    end)
end

add_cflags("-Wall", "-Wextra", "-Werror", "-Wshadow", "-Wconversion", "-pedantic")
add_cxxflags("-Wall", "-Wextra", "-Werror", "-Wshadow", "-Wconversion", "-pedantic")

for _, kind in pairs({"static", "shared", "object"}) do
    target("ez-string-"..kind, function()
        set_kind(kind)
        set_basename("ez-string")

        for short_san, long_san in pairs(sanitizers) do 
            if has_config(short_san) then
                set_policy("build.sanitizer."..long_san, true)
            end
        end

        if kind == "static" or kind == "shared" then
			add_headerfiles("src/ez-string.h", {install=true})
            set_default(true)
        else
			add_headerfiles("src/ez-string.h", {install=false})
            set_default(false)
        end
        add_files("src/*.c")
    end)
end

for _, file in ipairs(os.files("test/*.cpp")) do
    local name = path.basename(file)
    target(name, function()
        set_kind("binary")

        for short_san, long_san in pairs(sanitizers) do 
            if has_config(short_san) then
                set_policy("build.sanitizer."..long_san, true)
            end
        end

        set_default(false)
        add_includedirs("src")
		add_headerfiles("test/*.hpp", {install=false})
        add_packages("gtest")
        add_links("gtest_main")
        add_files("test/"..name..".cpp")
        add_deps("ez-string-object")
        add_tests("test", {realtime_output = true})
    end)
end
