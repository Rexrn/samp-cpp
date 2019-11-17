#include SAMPCPP_EXT_RESOURCEIO_PCH

#include <SAMPCpp/Ext/ResourceIO/XMLGlobalObjectDeserializer.hpp>
#include <SAMPCpp/Ext/ResourceIO/XMLHelperFunctions.hpp>
#include <SAMPCpp/Ext/ResourceIO/XMLNames.hpp>

namespace samp_cpp::ext::resource_io
{

///////////////////////////////////////////////////////////////////////////
bool XMLGlobalObjectDeserializer::deserialize() const
{
	if ( !this->deserializeModelIndex() )
		return false;

	this->deserializeDrawDistance();

	if ( !this->deserializeLocation() )
		return false;

	if ( !this->deserializeRotation() )
		return false;

	this->deserializeMaterials();

	return true;

}

}
