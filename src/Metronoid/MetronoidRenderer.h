#pragma once

#include <wrl.h>
#include "DirectXBase.h"
#include "Interfaces\IMetronoidRenderer.h"

ref class MetronoidRenderer sealed : public DirectXBase, public IMetronoidRenderer
{
public:
	MetronoidRenderer();
	~MetronoidRenderer();
	virtual void CreateDeviceIndependentResources() override;
	virtual void CreateDeviceResources() override;
	virtual void CreateWindowSizeDependentResources() override;
	virtual void Render() override;
	void Update(float timeTotal, float timeDelta);

	void OnManipulationUpdated(Windows::UI::Input::GestureRecognizer^ sender, Windows::UI::Input::ManipulationUpdatedEventArgs^ args);
	void OnManipulationCompleted(Windows::UI::Input::GestureRecognizer^ sender, Windows::UI::Input::ManipulationCompletedEventArgs^ args);
	void OnTapped(Windows::UI::Input::GestureRecognizer^ sender, Windows::UI::Input::TappedEventArgs^ args);

	void BeginDraw();
	virtual void Clear(Windows::UI::Color fillColor) override;
	void EndDraw();

#pragma region Primitive render functions
	virtual void FillRectangle(geom::Rect destination, Windows::UI::Color fillColor) override;
	virtual void FillEllipse(geom::Point point, float radiusX, float radiusY, Windows::UI::Color fillColor) override;
#pragma endregion

	void UpdateView(Windows::Foundation::Point deltaViewPosition);
	void SetRenderFast(bool value);
	void BackgroundColorNext();
	void BackgroundColorPrevious();

private:
	Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> m_blackBrush;
	Microsoft::WRL::ComPtr<IDWriteTextFormat> m_textFormat;
	Microsoft::WRL::ComPtr<ID2D1Bitmap1> m_opacityBitmap;
	Microsoft::WRL::ComPtr<IDWriteTextLayout> m_textLayout;
	DWRITE_TEXT_METRICS m_textMetrics;
	Windows::Foundation::Point m_viewPosition;
	bool m_animating;
	bool m_renderNeeded;
	int m_bgColorIndex;
};