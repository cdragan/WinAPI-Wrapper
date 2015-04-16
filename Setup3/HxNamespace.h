
#pragma once

class Buffer {
	std::vector< char > buffer;
	size_t pos;
	size_t limit;
	size_t begin_pos;
public:
	Buffer(): pos( 0 ), limit( 0 ), begin_pos( 0 ) { }
	std::vector< char >& Access() { return buffer; }
	int GetNumLeft() const { return static_cast<int>( buffer.size() - pos ); }
	void SetLimit( int lim ) { limit = pos + lim; }
	void BeginObject( int type );
	void EndObject();
	void Read( void* buffer, int size );
	void Write( const void* buffer, int size );

	template< class T >
	void Read( T& var ) {
		Read( &var, sizeof(var) );
	}
	template<>
	void Read( std::string& var ) {
		int length = 0;
		Read( length );
		var.resize( length );
		Read( &var[0], length );
		for ( int i=1; i < length>>1; i++ )
			var[i] = var[i*2];
		var.resize( length >> 1 );
	}
	template< class T >
	void Write( const T& var ) {
		Write( &var, sizeof(var) );
	}
	template<>
	void Write( const std::string& var ) {
		const int length = static_cast<int>( var.length() << 1 );
		Write( length );
		std::string buf( length, '\0' );
		for ( size_t i=0; i < var.length(); i++ )
			buf[i*2] = var[i];
		Write( buf.data(), length );
	}
};

class Object {
	int type;
public:
	Object( int type ): type( type ) { }
	int GetType() const { return type; }
	virtual void Read( Buffer& buffer ) = 0;
	virtual void Write( Buffer& buffer ) const = 0;
};

class ONamespace: public Object {
public:
	std::string namesp;
	std::string collection_file;
	std::string description;

	ONamespace(): Object( 2 ) { }
	virtual void Read( Buffer& buffer );
	virtual void Write( Buffer& buffer ) const;
};

class OFilter: public Object {
public:
	std::string name;
	std::string definition;

	OFilter(): Object( 3 ) { }
	virtual void Read( Buffer& buffer );
	virtual void Write( Buffer& buffer ) const;
};

class OLink: public Object {
public:
	std::string namesp;
	std::string parent_topic_file;
	std::string topic_file;
	std::string attr_file;

	OLink(): Object( 4 ) { }
	virtual void Read( Buffer& buffer );
	virtual void Write( Buffer& buffer ) const;
};

class OTitle: public Object {
public:
	std::string title_id;
	std::string title_file;
	std::string index_file;
	std::string query_file;
	std::string attr_file;
	int lang_id;
	int title_locate;
	int index_locate;
	int query_locate;
	int attr_locate;
	int mysterious_zero;

	OTitle(): Object( 5 ) { }
	virtual void Read( Buffer& buffer );
	virtual void Write( Buffer& buffer ) const;
};

class OLocate: public Object {
public:
	int index;
	std::string name;
	std::string path;

	OLocate(): Object( 6 ) { }
	virtual void Read( Buffer& buffer );
	virtual void Write( Buffer& buffer ) const;
};

class OUnknown: public Object {
public:
	std::string data;

	OUnknown( int type, int size ): Object( type ), data( size, '\0' ) { }
	virtual void Read( Buffer& buffer );
	virtual void Write( Buffer& buffer ) const;
};

class ObjectList {
	int type;
	std::vector< Object* > objects;
public:
	ObjectList( int type = -1 ): type( type ) { }
	~ObjectList();
	int GetType() const { return type; }
	int GetNumObjects() const { return static_cast<int>( objects.size() ); }
	int GetObjectType( int index ) const { return objects.at( index )->GetType(); }
	void RemoveObject( int index );
	template< class T >
	T* GetObject( int index ) const {
		T temp;
		if ( temp.GetType() != GetObjectType( index ) )
			return 0;
		return reinterpret_cast<T*>( objects[index] );
	}
	bool Read( const std::string& filename );
	bool Write( const std::string& filename );

	void AddNamespace( const std::string& namesp, const std::string& collection_file, const std::string& description );
	void AddFilter( const std::string& name, const std::string& definition );
	void AddLink( const std::string& namesp, const std::string& parent_topic_file, const std::string& topic_file, const std::string& attr_file );
	void AddTitle( const std::string& title_id, const std::string& title_file, const std::string& index_file, const std::string& query_file, const std::string& attr_file, int lang_id, int title_locate, int index_locate, int query_locate, int attr_locate );
	void AddLocate( int index, const std::string& name, const std::string& path );

private:
	void AddObject( Object* p_object );
	void Read( Buffer& buffer );
	void Write( Buffer& buffer );
};

void RegisterNamespace( const std::string& directory, const std::string& ns_name, const std::string& file_name, const std::string& description );

void DeregisterNamespace( const std::string& ns_name );

