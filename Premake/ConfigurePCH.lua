-- Configures PCH for current project
-- Example:
-- - projectName: Engine
-- - macro: SAMPCPP_PCH
-- Results in:
-- - pchheader "include/Engine/EnginePCH.hpp"
-- - pchsource "src/EnginePCH.hpp"
-- - SAMPCPP_PCH="include/Engine/EnginePCH.hpp"
-----^^^^^^^^^^^^^^^^^ - defined macro
edge.configurePCH = function (pchHeader, pchSource, pchMacro)
	pchheader (pchHeader)
	pchsource (pchSource)
	defines { pchMacro .. "=\"" .. pchHeader .. "\"" }
	includedirs { "." }
end