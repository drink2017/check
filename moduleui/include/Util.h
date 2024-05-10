#include <QWidget>
#include <QProxyStyle>
namespace ui
{
	namespace Util
	{
		/*
		间隔控件
		*/
		class SpacerWidget : public QWidget
		{
			Q_OBJECT
		public:
			SpacerWidget(QWidget* Parent = 0);
			virtual QSize sizeHint() const override { return QSize(0, 0); }
			virtual QSize minimumSizeHint() const override { return QSize(0, 0); }
		};

		/*
		h-shadow：水平阴影的位置，可以为正值（向右偏移）或负值（向左偏移）。
		v-shadow：垂直阴影的位置，可以为正值（向下偏移）或负值（向上偏移）。
		blur：模糊半径，可选参数，指定用于阴影的模糊程度。
		color：阴影的颜色。
		*/
		void addShadow(QWidget* widget, qreal hShadow, qreal vShadow, qreal blur, QColor color);

		/*
		设置QMenu中icon的大小
		*/
		class MenuIconStyle : public QProxyStyle {
			Q_OBJECT
		public:
			virtual int pixelMetric(PixelMetric metric, const QStyleOption* option, const QWidget* widget) const;

			void setIconSize(const int& size);

		private:
			int m_size;
		};
	}

}

