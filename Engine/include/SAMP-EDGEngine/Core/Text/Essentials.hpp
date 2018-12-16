#pragma once
#include SAMPEDGENGINE_PCH



namespace samp_edgengine::text
{
/// <summary>
/// Lits of popular encodings.
/// </summary>
enum class Encoding
{
	ASCII,
	UTF8,
	UTF16,
	UTF32
};

/// <summary>
/// String comparison settings.
/// </summary>
enum CaseSensitivity
{
	CaseInsensitive,
	CaseSensitive
};

} // namespace