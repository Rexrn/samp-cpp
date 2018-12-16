-- This is configuration file for build environment generation.
-- 
-- To properly configure build:
--  1) Copy BuildConfig.lua.template to new file and name it BuildConfig.user.lua
--  2) Fill in essential information
-- Use Lua syntax.

userConfig = {
	
	-- Build configuration:
	build = {
		thirdParty = true,
		extensions = true,
		examples = true,
		unitTests = true
	},
	
	-- Dependencies configuration:
	deps = {
		-- [Required]
		-- Please provide path to the root of the SAMPGDK library.
		sampgdk = { root = os.realpath("ThirdParty/SAMPGDK") }, 
	
		-- [Required]
		-- Please provide path to the root of the QuickMaffs library.
		quickmaffs = { root = "" },
		
		-- [Required if building examples]
		-- Please provide path to the root of the RapidXML library.
		rapidxml = { root = "" },

		-- [Required if building unit tests]
		-- Please provide path to the root of the googletest library.
		gtest = { root = "" }
	}
}