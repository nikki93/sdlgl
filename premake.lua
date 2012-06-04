---------------------------------------------------------------------------------------------
------------------------------------------- sdlgl -------------------------------------------
---------------------------------------------------------------------------------------------

-- Project ----------------------------------------------------------------------------------

project.name = "sdlgl"
project.bindir = "bin"

-- Package ----------------------------------------------------------------------------------

package = newpackage()

package.name = "sdlgl"
package.kind = "exe"
package.language = "c++"
package.configs = { "Debug", "Release" }

if (windows) then
   table.insert(package.defines, "WIN32") -- Needed to fix something on Windows.
end

-- Include and library search paths, system dependent ---------------------------------------

package.includepaths = {
    -- project
    "./src",
    "./src/fw",

    -- libraries
}

-- Libraries to link to ---------------------------------------------------------------------

package.links = {
    "GL",
    "GLU",
    "SDL"
}

-- Files ------------------------------------------------------------------------------------

package.files = {
matchrecursive("*.h", "*.cpp"),
}

-- Debug configuration ----------------------------------------------------------------------

debug = package.config["Debug"]
debug.defines = { "DEBUG", "_DEBUG" }
debug.objdir = "obj/debug"
debug.target = "debug/" .. package.name .. "_d"

debug.buildoptions = { "-g" }

-- Release configuration --------------------------------------------------------------------

release = package.config["Release"]
release.objdir = "obj/release"
release.target = "release/" .. package.name
