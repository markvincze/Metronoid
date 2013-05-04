//
// BlankPage.xaml.h
// Declaration of the BlankPage.xaml class.
//

#pragma once

#include "DirectXPage.g.h"
#include "MetronoidRenderer.h"
#include "BasicTimer.h"
#include "Game\Game.h"

namespace Metronoid
{
	/// <summary>
	/// A DirectX page that can be used on its own.  Note that it may not be used within a Frame.
	/// </summary>
    [Windows::Foundation::Metadata::WebHostHidden]
	public ref class DirectXPage sealed
	{
	public:
		DirectXPage();
		virtual ~DirectXPage();

		void CycleColorPrevious(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void CycleColorNext(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);

	private:
		void OnPointerMoved(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ args);
		void OnPointerReleased(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ args);
		void OnWindowSizeChanged(Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::WindowSizeChangedEventArgs^ args);
		void OnLogicalDpiChanged(Platform::Object^ sender);
		void OnRendering(Object^ sender, Object^ args);
		void OnTapped(Platform::Object^ sender, Windows::UI::Xaml::Input::TappedRoutedEventArgs^ e);

		Windows::Foundation::EventRegistrationToken m_eventToken;

		float x;
		float s;

		game::Game^ game;

		MetronoidRenderer^ m_renderer;
		bool m_renderNeeded;

		Windows::Foundation::Point m_lastPoint;
		bool m_lastPointValid;
		
		BasicTimer^ m_timer;
	};
}
