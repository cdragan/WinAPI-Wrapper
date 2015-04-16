
#include "stdafx.h"
#include "HxNamespace.h"

void Buffer::BeginObject( int type )
{
	Write( type );
	const int length = 0;
	Write( length );
	begin_pos = pos;
}

void Buffer::EndObject()
{
	*reinterpret_cast<int*>( &buffer[begin_pos-sizeof(int)] ) = static_cast<int>( pos - begin_pos );
}

void Buffer::Read( void* data, int size )
{
	if ( pos + size > limit || pos + size > buffer.size() )
		throw "Damaged file";
	memcpy( data, &buffer[pos], size );
	pos += size;
}

void Buffer::Write( const void* data, int size )
{
	const size_t req_len = pos + size;
	if ( buffer.size() < req_len )
		buffer.resize( req_len );
	memcpy( &buffer[pos], data, size );
	pos += size;
}

void ONamespace::Read( Buffer& buffer )
{
	buffer.Read( namesp );
	buffer.Read( collection_file );
	buffer.Read( description );
}

void ONamespace::Write( Buffer& buffer ) const
{
	buffer.BeginObject( GetType() );
	buffer.Write( namesp );
	buffer.Write( collection_file );
	buffer.Write( description );
	buffer.EndObject();
}


void OFilter::Read( Buffer& buffer )
{
	buffer.Read( name );
	buffer.Read( definition );
}

void OFilter::Write( Buffer& buffer ) const
{
	buffer.BeginObject( GetType() );
	buffer.Write( name );
	buffer.Write( definition );
	buffer.EndObject();
}

void OLink::Read( Buffer& buffer )
{
	buffer.Read( namesp );
	buffer.Read( parent_topic_file );
	buffer.Read( topic_file );
	buffer.Read( attr_file );
}

void OLink::Write( Buffer& buffer ) const
{
	buffer.BeginObject( GetType() );
	buffer.Write( namesp );
	buffer.Write( parent_topic_file );
	buffer.Write( topic_file );
	buffer.Write( attr_file );
	buffer.EndObject();
}

void OTitle::Read( Buffer& buffer )
{
	buffer.Read( title_id );
	buffer.Read( title_file );
	buffer.Read( index_file );
	buffer.Read( query_file );
	buffer.Read( attr_file );
	buffer.Read( lang_id );
	buffer.Read( title_locate );
	buffer.Read( index_locate );
	buffer.Read( query_locate );
	buffer.Read( attr_locate );
	buffer.Read( mysterious_zero );
}

void OTitle::Write( Buffer& buffer ) const
{
	buffer.BeginObject( GetType() );
	buffer.Write( title_id );
	buffer.Write( title_file );
	buffer.Write( index_file );
	buffer.Write( query_file );
	buffer.Write( attr_file );
	buffer.Write( lang_id );
	buffer.Write( title_locate );
	buffer.Write( index_locate );
	buffer.Write( query_locate );
	buffer.Write( attr_locate );
	buffer.Write( mysterious_zero );
	buffer.EndObject();
}

void OLocate::Read( Buffer& buffer )
{
	buffer.Read( index );
	buffer.Read( name );
	buffer.Read( path );
}

void OLocate::Write( Buffer& buffer ) const
{
	buffer.BeginObject( GetType() );
	buffer.Write( index );
	buffer.Write( name );
	buffer.Write( path );
	buffer.EndObject();
}

void OUnknown::Read( Buffer& buffer )
{
	buffer.Read( &data[0], static_cast<int>( data.size() ) );
}

void OUnknown::Write( Buffer& buffer ) const
{
	buffer.BeginObject( GetType() );
	buffer.Write( data.data(), static_cast<int>( data.size() ) );
	buffer.EndObject();
}

ObjectList::~ObjectList()
{
	for ( size_t i=0; i < objects.size(); i++ )
		delete objects[i];
	objects.clear();
}

void ObjectList::AddObject( Object* p_object )
{
	objects.push_back( p_object );
}

void ObjectList::RemoveObject( int index )
{
	delete objects.at( index );
	objects.erase( objects.begin() + index );
}

void ObjectList::Read( Buffer& buffer )
{
	for ( size_t i=0; i < objects.size(); i++ )
		delete objects[i];
	objects.clear();

	if ( buffer.GetNumLeft() < 16 )
		throw "Damaged file";
	buffer.SetLimit( buffer.GetNumLeft() );
	buffer.Read( type );
	int zero[3];
	for ( int i=0; i < 3; i++ )
		buffer.Read( zero[i] );

	while ( buffer.GetNumLeft() ) {
		int type = 0;
		int length = 0;
		buffer.SetLimit( buffer.GetNumLeft() );
		buffer.Read( type );
		buffer.Read( length );
		buffer.SetLimit( length );
		std::auto_ptr<Object> p_object( 0 );
		switch ( type ) {
		case 2:  p_object = std::auto_ptr<Object>( new ONamespace ); break;
		case 3:  p_object = std::auto_ptr<Object>( new OFilter ); break;
		case 4:  p_object = std::auto_ptr<Object>( new OLink ); break;
		case 5:  p_object = std::auto_ptr<Object>( new OTitle ); break;
		case 6:  p_object = std::auto_ptr<Object>( new OLocate ); break;
		default: p_object = std::auto_ptr<Object>( new OUnknown( type, length ) ); break;
		}
		p_object->Read( buffer );
		AddObject( p_object.release() );
	}
}

void ObjectList::Write( Buffer& buffer )
{
	if ( type == -1 )
		throw "Damaged file";
	buffer.Write( type );
	const int zero = 0;
	for ( int i=0; i < 3; i++ )
		buffer.Write( zero );

	for ( size_t i=0; i < objects.size(); i++ )
		objects[i]->Write( buffer );
}

using namespace WinAPI;

bool ObjectList::Read( const std::string& filename )
{
	File file( filename.c_str(), OPEN_EXISTING, GENERIC_READ );
	if ( ! file.IsOpen() )
		return false;
	try {
		const int size = file.GetSize();
		Buffer buffer;
		std::vector< char >& bytes = buffer.Access();
		bytes.resize( size );
		if ( size != file.Read( &bytes[0], size ) )
			return false;
		Read( buffer );
	} catch ( const char* ) {
		return false;
	}
	return true;
}

bool ObjectList::Write( const std::string& filename )
{
	File file( filename.c_str(), CREATE_ALWAYS, GENERIC_WRITE, FILE_ATTRIBUTE_ARCHIVE | FILE_ATTRIBUTE_HIDDEN );
	if ( ! file.IsOpen() )
		return false;
	try {
		Buffer buffer;
		Write( buffer );
		std::vector< char >& bytes = buffer.Access();
		const int size = static_cast<int>( bytes.size() );
		if ( size != file.Write( &bytes[0], size ) )
			return false;
	} catch ( const char* ) {
		return false;
	}
	return true;
}

void ObjectList::AddNamespace( const std::string& namesp, const std::string& collection_file, const std::string& description )
{
	ONamespace* p_object = new ONamespace;
	p_object->namesp = namesp;
	p_object->collection_file = collection_file;
	p_object->description = description;
	AddObject( p_object );
}

void ObjectList::AddFilter( const std::string& name, const std::string& definition )
{
	OFilter* p_object = new OFilter;
	p_object->name = name;
	p_object->definition = definition;
	AddObject( p_object );
}

void ObjectList::AddLink( const std::string& namesp, const std::string& parent_topic_file, const std::string& topic_file, const std::string& attr_file )
{
	OLink* p_object = new OLink;
	p_object->namesp = namesp;
	p_object->parent_topic_file = parent_topic_file;
	p_object->topic_file = topic_file;
	p_object->attr_file = attr_file;
	AddObject( p_object );
}

void ObjectList::AddTitle( const std::string& title_id, const std::string& title_file, const std::string& index_file, const std::string& query_file, const std::string& attr_file, int lang_id, int title_locate, int index_locate, int query_locate, int attr_locate )
{
	OTitle* p_object = new OTitle;
	p_object->title_id = title_id;
	p_object->title_file = title_file;
	p_object->index_file = index_file;
	p_object->query_file = query_file;
	p_object->attr_file = attr_file;
	p_object->lang_id = lang_id;
	p_object->title_locate = title_locate;
	p_object->index_locate = index_locate;
	p_object->query_locate = query_locate;
	p_object->attr_locate = attr_locate;
	p_object->mysterious_zero = 0;
	AddObject( p_object );
}

void ObjectList::AddLocate( int index, const std::string& name, const std::string& path )
{
	OLocate* p_object = new OLocate;
	p_object->index = index;
	p_object->name = name;
	p_object->path = path;
	AddObject( p_object );
}

namespace {

	bool GetRegDir( std::string* p_dir )
	{
		assert( p_dir != 0 );
		RegKey key;
		if ( 0 != key.OpenMachine( "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Shell Folders", KEY_READ ) )
			return false;
		if ( 0 != key.QueryValue( "Common AppData", p_dir ) )
			return false;
		*p_dir += "\\Microsoft Help\\";
		return true;
	}

	std::string BackslashToSlash( const std::string& input )
	{
		std::string s = input;
		for ( size_t i=0; i < s.length(); i++ )
			if ( s[i] == '\\' )
				s[i] = '/';
		return s;
	}

}

void RegisterNamespace( const std::string& in_directory, const std::string& ns_name, const std::string& file_name, const std::string& description )
{
	// Make directory path valid
	std::string directory = in_directory;
	if ( ! directory.empty() && directory[ directory.size()-1 ] != '\\' )
		directory += '\\';

	// Get help registration folder
	std::string regdir;
	if ( ! GetRegDir( &regdir ) )
		return;

	// Create namespace file
	ObjectList namespace_file( 4 );
	namespace_file.AddTitle( ns_name, file_name+".HxS", file_name+".HxI", "", "", 1033, 1, 1, 0, 0 );
	namespace_file.AddLocate( 1, directory, directory );
	if ( ! namespace_file.Write( regdir+ns_name+".hxn" ) )
		return;

	// Add namespace to the list of namespaces
	ObjectList namespace_list;
	if ( ! namespace_list.Read( regdir+"nslist.hxl" ) )
		return;
	namespace_list.AddNamespace( ns_name, directory+file_name+".HxC", description );
	if ( ! namespace_list.Write( regdir+"nslist.hxl" ) )
		return;

	// Register namespace in the VSCC collection
	ObjectList vscc_list;
	if ( ! vscc_list.Read( regdir+"MS.VSCC.hxn" ) )
		return;
	int i = 0;
	for ( ; i < vscc_list.GetNumObjects(); i++ )
		if ( vscc_list.GetObjectType(i) == 4 )
			break;
	if ( i >= vscc_list.GetNumObjects() )
		return;
	OLink* p_link = vscc_list.GetObject<OLink>( i );
	const std::string parent_dir = p_link->parent_topic_file;
	vscc_list.AddLink( ns_name, parent_dir, BackslashToSlash(directory+file_name+".HxT"), directory+file_name+".HxA" );
	if ( ! vscc_list.Write( regdir+"MS.VSCC.hxn" ) )
		return;
}

void DeregisterNamespace( const std::string& ns_name )
{
	// Get help registration folder
	std::string regdir;
	if ( ! GetRegDir( &regdir ) )
		return;

	// Remove namespace file
	DeleteFile( (regdir+ns_name+".hxn").c_str() );

	// Remove namespace from the list of namespaces
	ObjectList namespace_list;
	if ( ! namespace_list.Read( regdir+"nslist.hxl" ) )
		return;
	bool b_modified = false;
	for ( int i=0; i < namespace_list.GetNumObjects(); i++ )
		if ( namespace_list.GetObjectType( i ) == 2 ) {
			ONamespace* p_ns = namespace_list.GetObject<ONamespace>( i );
			if ( p_ns->namesp == ns_name ) {
				namespace_list.RemoveObject( i );
				b_modified = true;
				break;
			}
		}
	if ( b_modified )
		namespace_list.Write( regdir+"nslist.hxl" );

	// Remove namespace from the VSCC collection
	ObjectList vscc_list;
	if ( ! vscc_list.Read( regdir+"MS.VSCC.hxn" ) )
		return;
	b_modified = false;
	for ( int i=0; i < vscc_list.GetNumObjects(); i++ )
		if ( vscc_list.GetObjectType( i ) == 4 ) {
			OLink* p_link = vscc_list.GetObject<OLink>( i );
			if ( p_link->namesp == ns_name ) {
				vscc_list.RemoveObject( i );
				b_modified = true;
				break;
			}
		}
	if ( b_modified )
		vscc_list.Write( regdir+"MS.VSCC.hxn" );
}
