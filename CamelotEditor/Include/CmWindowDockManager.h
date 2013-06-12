#pragma once

#include "CmEditorPrerequisites.h"
#include "CmModule.h"
#include "CmQtDockOverlayWidget.h"

namespace CamelotEditor
{
	class WindowDockManager : public Module<WindowDockManager>
	{
		struct DockedWindowInfo
		{
			INT32 parentId;
			WindowDragDropLocation dockLocation;
		};

	public:
		WindowDockManager(QWidget* centralWidget, QtDockOverlayWidget* dockWidget);

		void windowDragged(QtEditorWindow* window, const QPoint& mousePos);
		void windowReleased(QtEditorWindow* window, const QPoint& mousePos);
		void windowClosed(QtEditorWindow* window);

		void dockWindow(QtEditorWindow* windowToDock, QtEditorWindow* dockAtWidget, WindowDragDropLocation dockAtPosition);
		void undockWindow(QtEditorWindow* windowToUndock);

		bool isDocked(const QtEditorWindow* window) const;
		WindowDragDropLocation getDockLocation(const QtEditorWindow* window) const;
		INT32 getDockParentId(const QtEditorWindow* window) const;
	private:
		QtDockOverlayWidget* mDockOverlayWidget;
		QWidget* mCentralWidget;
		QSplitter* mCentralSplitter;
		QtEditorWindow* mLastDraggedWindow;
		QPoint mLastDragPosition;

		Map<QtEditorWindow*, DockedWindowInfo>::type mDockedWindows;

		bool isPositionInDockArea(const QPoint& globalPos);

		WindowDragDropLocation getDropLocationAtPosition(const QWidget* widget, const QPoint& globalPos);
		std::vector<QPolygon> getDropLocations(const QWidget* widget);
	};

	WindowDockManager& gWindowDockManager();
}