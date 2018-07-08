#include "ResourceIOPCH.hpp"

#include <SAMP-EDGEngine-Ext/ResourceIO/XMLGlobalObjectDeserializer.hpp>
#include <SAMP-EDGEngine-Ext/ResourceIO/XMLHelperFunctions.hpp>
#include <SAMP-EDGEngine-Ext/ResourceIO/XMLNames.hpp>

namespace samp_edgengine::ext::resource_io
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
