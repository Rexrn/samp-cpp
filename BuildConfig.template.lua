-- This is configuration file for build environment generation.
-- 
-- To properly configure build:
--  1) Copy BuildConfig.lua.template to new file and name it BuildConfig.user.lua
--  2) Fill in essential information
-- Use Lua syntax.

userConfig = {
	
	-- Build configuration:
	build = {
		extensions = true,
		examples = true,
		unitTests = true,
		thirdParty = true
	},
	
	-- Dependencies configuration:
	deps = {
		-- [Required]
		-- Please provide path to the root of the SAMP Plugin SDK library.
		samp_plugin_sdk = { root = "" }, 
	
		-- [Required]
		-- Please provide path to the root of the SAMPGDK library.
		sampgdk = { root = "" }, 
	
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