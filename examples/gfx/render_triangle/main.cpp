#include <core/gfx/render_system_factory.hpp>
#include <core/gfx/win32/render_window.hpp>
#include <gl4/render_system.hpp>

using namespace morpheus::gfx;

class Application {
public:
    void Run()
    {

    }
};

class ExampleFramework 
{
public:

	//! Destructor.
	virtual ~ExampleFramework() {}

	/*!
		*/
	virtual void Create()
	{		
	}

	/*!
		*/
	virtual void Destroy()
	{
	}

	void Run()
	{
		while ( true ) 
		{
//			#pragma FREEDOM_TODO( "Hide message pump behind Freedom operating system abstraction")

			::MSG msg;
			::ZeroMemory( &msg, sizeof(msg) );

			// While there is messages in the queue pump them 
			// till the message queue until it is empty
			while (::PeekMessage( &msg, NULL, 0, 0, PM_NOREMOVE ) )
			{
				if( ::GetMessage( &msg, NULL, 0, 0 ) )
				{
					::TranslateMessage( &msg );
					::DispatchMessage( &msg );
				}
			}
		}
	}

	ExampleFramework() = default;

protected:
	win32::RenderWindow window;
};

int main(int argc, char *argv[])
{
	ExampleFramework example;
	example.Run();
//    render_system_factory renderer_factory;
}