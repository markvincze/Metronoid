//
// BlankPage.xaml.cpp
// Implementation of the BlankPage.xaml class.
//

#include "pch.h"
#include "DirectXPage.xaml.h"
#include "Geometry\Point.h"

using namespace Metronoid;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Input;
using namespace Windows::UI::Core;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;
using namespace Windows::Graphics::Display;

DirectXPage::DirectXPage() :
	m_renderNeeded(true),
	m_lastPointValid(false),
	game(ref new game::Game(geom::Size(Window::Current->CoreWindow->Bounds.Width, Window::Current->CoreWindow->Bounds.Height))),
	x(0),
	s(80)
{
	InitializeComponent();

	m_renderer = ref new MetronoidRenderer();

	m_renderer->Initialize(
		Window::Current->CoreWindow,
		this,
		DisplayProperties::LogicalDpi
		);

	Window::Current->CoreWindow->SizeChanged += 
		ref new TypedEventHandler<CoreWindow^, WindowSizeChangedEventArgs^>(this, &DirectXPage::OnWindowSizeChanged);

	DisplayProperties::LogicalDpiChanged +=
		ref new DisplayPropertiesEventHandler(this, &DirectXPage::OnLogicalDpiChanged);

	m_eventToken = CompositionTarget::Rendering::add(ref new EventHandler<Object^>(this, &DirectXPage::OnRendering));

	m_timer = ref new BasicTimer();
}

DirectXPage::~DirectXPage()
{
}

void DirectXPage::OnPointerMoved(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ args)
{
	auto currentPoint = args->GetCurrentPoint(nullptr);
	/*if (currentPoint->IsInContact)
	{*/
		/*if (m_lastPointValid)
		{
		Windows::Foundation::Point delta(
		currentPoint->Position.X - m_lastPoint.X,
		currentPoint->Position.Y - m_lastPoint.Y
		);
		m_renderer->UpdateView(delta);
		m_renderNeeded = true;
		}*/
		m_lastPoint = currentPoint->Position;
	/*	m_lastPointValid = true;
	}
	else
	{
		m_lastPointValid = false;
	}*/
}

void DirectXPage::OnPointerReleased(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ args)
{
	m_lastPointValid = false;
}

void DirectXPage::OnWindowSizeChanged(CoreWindow^ sender, WindowSizeChangedEventArgs^ args)
{
	m_renderer->UpdateForWindowSizeChange();
	m_renderNeeded = true;
}

void DirectXPage::OnLogicalDpiChanged(Platform::Object^ sender)
{
	m_renderer->SetDpi(DisplayProperties::LogicalDpi);
	m_renderNeeded = true;
}

void DirectXPage::OnRendering(Platform::Object^ sender, Platform::Object^ args)
{
	m_timer->Update();

	txtFps->Text = (1 / m_timer->Delta).ToString();
	game->Step(m_timer->Delta, geom::Point(m_lastPoint.X, m_lastPoint.Y));

	m_renderer->BeginDraw();
	game->Render(m_renderer);
	m_renderer->EndDraw();
	m_renderer->Present();
}

void DirectXPage::CycleColorPrevious(Platform::Object^ sender, RoutedEventArgs^ args)
{
	m_renderer->BackgroundColorNext();
	m_renderNeeded = true;
}

void DirectXPage::CycleColorNext(Platform::Object^ sender, RoutedEventArgs^ args)
{
	m_renderer->BackgroundColorPrevious();
	m_renderNeeded = true;
}
