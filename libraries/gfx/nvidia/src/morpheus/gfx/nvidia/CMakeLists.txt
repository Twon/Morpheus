target_sources(MorpheusGfxNVidia
	PUBLIC
		adapter.hpp
		driver.hpp
	PRIVATE
		adapter.cpp
		driver.cpp
)

target_link_libraries(MorpheusGfxNVidia
	PUBLIC
		Boost::filesystem
	PRIVATE
		NVidia::NvapiHeaders
)