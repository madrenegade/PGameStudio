#include "renderingdockwidget.h"
#include "ui_renderingdockwidget.h"

#include "controller.h"

RenderingDockWidget::RenderingDockWidget(Controller* controller, QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::RenderingDockWidget), controller(controller)
{
    ui->setupUi(this);

    auto availableSystems(controller->availableSystems());

    auto debugDrawingTab = ui->tabDebugDrawing;

    for(auto i = availableSystems.begin(); i != availableSystems.end(); ++i)
    {
        auto checkBox = new QCheckBox(*i, debugDrawingTab);
        debugDrawingTab->layout()->addWidget(checkBox);
        debugDrawingCheckBoxes.append(checkBox);
    }
}

RenderingDockWidget::~RenderingDockWidget()
{
    delete ui;
}
