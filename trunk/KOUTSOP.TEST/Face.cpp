//-----------------------------------------------------------------------------
// File: CreateDevice.cpp
//
// Desc: This is the first tutorial for using Direct3D. In this tutorial, all
//       we are doing is creating a Direct3D device and using it to clear the
//       window.
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------
#include <d3d9.h>
#pragma warning( disable : 4996 ) // disable deprecated warning 
#include <strsafe.h>
#pragma warning( default : 4996 ) 
#include <assert.h>


//-----------------------------------------------------------------------------
// Global variables
//-----------------------------------------------------------------------------
LPDIRECT3D9             g_pD3D       = NULL; // Used to create the D3DDevice
LPDIRECT3DDEVICE9       g_pd3dDevice = NULL; // Our rendering device

//---------------Code injection -----------------------------------
const int g_width=20000;
const int g_height = 480;

struct point_vertex{
    float x, y, z, rhw;  // The transformed(screen space) position for the vertex.
    DWORD colour;        // The vertex colour.
};

const DWORD point_fvf=D3DFVF_XYZRHW|D3DFVF_DIFFUSE;
point_vertex random_data[g_width];
int index=0;

void draw_point(int x, int y){
	if(index == g_width){
		assert(0);
	}
	random_data[++index].x = x;
	random_data[index].y = y;
	random_data[index].z=1.0f;
	random_data[index].rhw=1.0f;
	random_data[index].colour=D3DCOLOR_XRGB(200,200,200);
	return ;
}

void midpoint_ellipse(int a, int b, int centerX, int centerY, int xmask, int ymask){
	   double d2;
       float x=0;
       float y=b;//(float)b;
       double d1=(b*b)-((a*a)*b)+(0.25*(a*a));
       double tmp;

       draw_point(xmask*x+centerX,ymask*y+centerY);
       tmp =(a*a)*(y-0.5)-(b*b)*(x+1);
       while(tmp>0){
               if(d1<0)
                       d1+=(b*b)*(2*x+3);
               else{
                       d1+=(b*b)*(2*x+3)+(a*a)*(2-2*y);
                       y--;
               }
               x++;
		       draw_point(xmask*x+centerX,ymask*y+centerY);
		       tmp =(a*a)*(y-0.5)-(b*b)*(x+1);
	   }
       d2 = (b*b)*((x+0.5)*(x+0.5)) + (a*a)*((y-1)*(y-1)) - (a*a)*(b*b);
       
	   while(y>0){
               if(d2<0){
                       d2+=(b*b)*(2*x+2)+(a*a)*(3-2*y);
                       x++;
               } else
                       d2+=(a*a)*(3-2*y);
               y--;
		       draw_point(xmask*x+centerX,ymask*y+centerY);
	   }
	   
       return ;	
}

//----------------------------------------------------


//----------------------------------------------
// MakeEclipse
//------------------------------------------
void MakeEclipse(int a, int b, int centerX, int centerY){
	midpoint_ellipse(a, b, centerX, centerY, 1, 1);
	midpoint_ellipse(a, b, centerX, centerY, 1, -1);
	midpoint_ellipse(a, b, centerX, centerY, -1, 1);
	midpoint_ellipse(a, b, centerX, centerY, -1, -1);

	return;
}

//-----------------------------------------------------
// MakeHorLine
//----------------------------------------------------
void MakeHorLine(int startX, int startY, int width){
	for(int y=startX;y < startX+width;++y)
		draw_point(y, startY);
	return;
	}

//-----------------------------------------------------------------------------
// Name: InitD3D()
// Desc: Initializes Direct3D

//-----------------------------------------------------------------------------
HRESULT InitD3D( HWND hWnd )
{
    // Create the D3D object, which is needed to create the D3DDevice.
    if( NULL == ( g_pD3D = Direct3DCreate9( D3D_SDK_VERSION ) ) )
        return E_FAIL;

    // Set up the structure used to create the D3DDevice. Most parameters are
    // zeroed out. We set Windowed to TRUE, since we want to do D3D in a
    // window, and then set the SwapEffect to "discard", which is the most
    // efficient method of presenting the back buffer to the display.  And 
    // we request a back buffer format that matches the current desktop display 
    // format.
    D3DPRESENT_PARAMETERS d3dpp; 
    ZeroMemory( &d3dpp, sizeof(d3dpp) );
    d3dpp.Windowed = TRUE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;

    // Create the Direct3D device. Here we are using the default adapter (most
    // systems only have one, unless they have multiple graphics hardware cards
    // installed) and requesting the HAL (which is saying we want the hardware
    // device rather than a software one). Software vertex processing is 
    // specified since we know it will work on all cards. On cards that support 
    // hardware vertex processing, though, we would see a big performance gain 
    // by specifying hardware vertex processing.
    if( FAILED( g_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
                                      D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                                      &d3dpp, &g_pd3dDevice ) ) )
    {
        return E_FAIL;
    }

    // Device state would normally be set here
	g_pd3dDevice->SetFVF(point_fvf);
    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: Cleanup()
// Desc: Releases all previously initialized objects
//-----------------------------------------------------------------------------
VOID Cleanup()
{
    if( g_pd3dDevice != NULL) 
        g_pd3dDevice->Release();

    if( g_pD3D != NULL)
        g_pD3D->Release();
}



//-----------------------------------------------------------------------------
// Name: Render()
// Desc: Draws the scene
//-----------------------------------------------------------------------------
VOID Render()
{
    if( NULL == g_pd3dDevice )
        return;

    // Clear the backbuffer to a blue color
    g_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0,0,0), 1.0f, 0 );
    
    // Begin the scene
    
    g_pd3dDevice->BeginScene();
        // Rendering of scene objects can happen here
		MakeEclipse(150, 100, 400, 300); //face
		MakeEclipse( 20, 20, 300, 330); // left eye
		MakeEclipse( 20, 20, 500, 300); // right eye
		MakeEclipse( 0, 20, 400, 300); // Nose
		MakeHorLine(330, 350, 100);
//		MakeEclipse( 20, 0, 400, 350); // Nose

		g_pd3dDevice->DrawPrimitiveUP(D3DPT_POINTLIST,        //PrimitiveType
                                 g_width,                //PrimitiveCount
                                 random_data,                   //pVertexStreamZeroData
                                 sizeof(point_vertex));  //VertexStreamZeroStride

        // End the scene
        g_pd3dDevice->EndScene();

    // Present the backbuffer contents to the display
    g_pd3dDevice->Present( NULL, NULL, NULL, NULL );
}




//-----------------------------------------------------------------------------
// Name: MsgProc()
// Desc: The window's message handler
//-----------------------------------------------------------------------------
LRESULT WINAPI MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
    switch( msg )
    {
        case WM_DESTROY:
            Cleanup();
            PostQuitMessage( 0 );
            return 0;

        case WM_PAINT:
            Render();
            ValidateRect( hWnd, NULL );
            return 0;
    }

    return DefWindowProc( hWnd, msg, wParam, lParam );
}




//-----------------------------------------------------------------------------
// Name: wWinMain()
// Desc: The application's entry point
//----------------------------------------------------------------------------
INT WINAPI wWinMain( HINSTANCE hInst, HINSTANCE, LPWSTR, INT )
{
    // Register the window class
    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L, 
                      GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
                      L"D3D Tutorial", NULL };
    RegisterClassEx( &wc );

    // Create the application's window
    HWND hWnd = CreateWindow( L"D3D Tutorial", L"FaCe", 
                              WS_OVERLAPPEDWINDOW, 100, 100, 800, 600,
                              NULL, NULL, wc.hInstance, NULL );

    // Initialize Direct3D
    if( SUCCEEDED( InitD3D( hWnd ) ) )
    { 
        // Show the window
        ShowWindow( hWnd, SW_SHOWDEFAULT );
        UpdateWindow( hWnd );

        // Enter the message loop
        MSG msg; 
        while( GetMessage( &msg, NULL, 0, 0 ) )
        {
            TranslateMessage( &msg );
            DispatchMessage( &msg );
        }
    }

    UnregisterClass( L"D3D Tutorial", wc.hInstance );
    return 0;
}



