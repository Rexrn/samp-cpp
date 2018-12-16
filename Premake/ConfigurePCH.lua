-- Configures PCH for current project
-- Example:
-- - projectName: Engine
-- - macro: SAMPEDGENGINE_PCH
-- Results in:
-- - pchheader "include/Engine/EnginePCH.hpp"
-- - pchsource "src/EnginePCH.hpp"
-- - SAMPEDGENGINE_PCH="include/Engine/EnginePCH.hpp"
-----^^^^^^^^^^^^^^^^^ - defined macro
edge.configurePCH = function (pchHeader, pchSource, pchMacro)
	pchheader (pchHeader)
	pchsource (pchSource)
	defines { pchMacro .. "=\"" .. pchHeader .. "\"" }
	includedirs { "." }
end