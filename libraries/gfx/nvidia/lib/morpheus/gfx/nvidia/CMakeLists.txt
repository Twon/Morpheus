target_sources(MorpheusGfxNVidia
	PUBLIC
	    FILE_SET HEADERS
	    FILES
		    adapter.hpp
		    driver.hpp
		    functions.hpp
	PRIVATE
		adapter.cpp
		driver.cpp
)

target_link_libraries(MorpheusGfxNVidia
    PUBLIC
        Boost::filesystem
        NVidia::Nvapi
)
