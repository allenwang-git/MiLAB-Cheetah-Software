/********************************************************************************
** Form generated from reading UI file 'SimControlPanel.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIMCONTROLPANEL_H
#define UI_SIMCONTROLPANEL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SimControlPanel
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout_3;
    QFrame *frame_2;
    QVBoxLayout *verticalLayout;
    QLabel *simulatorStateLabel;
    QLabel *simulatorConnectedLabel;
    QFrame *frame;
    QGridLayout *gridLayout;
    QPushButton *startButton;
    QPushButton *driverButton;
    QPushButton *joystickButton;
    QPushButton *stopButton;
    QFrame *frame_9;
    QHBoxLayout *horizontalLayout_2;
    QRadioButton *MilabButton;
    QRadioButton *cheetah3Button;
    QRadioButton *miniCheetahButton;
    QFrame *frame_10;
    QHBoxLayout *horizontalLayout;
    QRadioButton *simulatorButton;
    QRadioButton *robotButton;
    QFrame *frame_13;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *setTerrainButton;
    QLabel *terrainFileLabel;
    QFrame *frame_14;
    QHBoxLayout *horizontalLayout_5;
    QCheckBox *hide_floor_checkbox;
    QCheckBox *hide_robot_checkbox;
    QLabel *label;
    QTableWidget *simulatorTable;
    QFrame *frame_6;
    QGridLayout *gridLayout_3;
    QPushButton *loadSimulatorButton;
    QPushButton *saveSimulatorButton;
    QFrame *frame_5;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_2;
    QTableWidget *robotTable;
    QFrame *frame_4;
    QGridLayout *gridLayout_2;
    QPushButton *loadRobotButton;
    QPushButton *saveRobotButton;
    QFrame *frame_12;
    QGridLayout *gridLayout_6;
    QFrame *frame_11;
    QVBoxLayout *verticalLayout_6;
    QLineEdit *kickAngularX;
    QLineEdit *kickAngularY;
    QLineEdit *kickAngularZ;
    QLineEdit *kickLinearX;
    QLineEdit *kickLinearY;
    QLineEdit *kickLinearZ;
    QPushButton *kickButton;
    QFrame *frame_3;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_3;
    QTableWidget *userControlTable;
    QFrame *frame_7;
    QGridLayout *gridLayout_4;
    QPushButton *loadUserButton;
    QPushButton *saveUserButton;
    QFrame *frame_8;
    QVBoxLayout *verticalLayout_4;
    QPushButton *goHomeButton;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *SimControlPanel)
    {
        if (SimControlPanel->objectName().isEmpty())
            SimControlPanel->setObjectName(QStringLiteral("SimControlPanel"));
        SimControlPanel->resize(1312, 1209);
        centralWidget = new QWidget(SimControlPanel);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout_3 = new QHBoxLayout(centralWidget);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        frame_2 = new QFrame(centralWidget);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        verticalLayout = new QVBoxLayout(frame_2);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        simulatorStateLabel = new QLabel(frame_2);
        simulatorStateLabel->setObjectName(QStringLiteral("simulatorStateLabel"));

        verticalLayout->addWidget(simulatorStateLabel);

        simulatorConnectedLabel = new QLabel(frame_2);
        simulatorConnectedLabel->setObjectName(QStringLiteral("simulatorConnectedLabel"));

        verticalLayout->addWidget(simulatorConnectedLabel);

        frame = new QFrame(frame_2);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout = new QGridLayout(frame);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        startButton = new QPushButton(frame);
        startButton->setObjectName(QStringLiteral("startButton"));

        gridLayout->addWidget(startButton, 0, 0, 1, 1);

        driverButton = new QPushButton(frame);
        driverButton->setObjectName(QStringLiteral("driverButton"));

        gridLayout->addWidget(driverButton, 1, 1, 1, 1);

        joystickButton = new QPushButton(frame);
        joystickButton->setObjectName(QStringLiteral("joystickButton"));

        gridLayout->addWidget(joystickButton, 0, 1, 1, 1);

        stopButton = new QPushButton(frame);
        stopButton->setObjectName(QStringLiteral("stopButton"));

        gridLayout->addWidget(stopButton, 1, 0, 1, 1);


        verticalLayout->addWidget(frame);

        frame_9 = new QFrame(frame_2);
        frame_9->setObjectName(QStringLiteral("frame_9"));
        frame_9->setFrameShape(QFrame::StyledPanel);
        frame_9->setFrameShadow(QFrame::Raised);
        horizontalLayout_2 = new QHBoxLayout(frame_9);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        MilabButton = new QRadioButton(frame_9);
        MilabButton->setObjectName(QStringLiteral("MilabButton"));
        MilabButton->setChecked(true);

        horizontalLayout_2->addWidget(MilabButton);

        cheetah3Button = new QRadioButton(frame_9);
        cheetah3Button->setObjectName(QStringLiteral("cheetah3Button"));

        horizontalLayout_2->addWidget(cheetah3Button);

        miniCheetahButton = new QRadioButton(frame_9);
        miniCheetahButton->setObjectName(QStringLiteral("miniCheetahButton"));

        horizontalLayout_2->addWidget(miniCheetahButton);


        verticalLayout->addWidget(frame_9);

        frame_10 = new QFrame(frame_2);
        frame_10->setObjectName(QStringLiteral("frame_10"));
        frame_10->setFrameShape(QFrame::StyledPanel);
        frame_10->setFrameShadow(QFrame::Raised);
        horizontalLayout = new QHBoxLayout(frame_10);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        simulatorButton = new QRadioButton(frame_10);
        simulatorButton->setObjectName(QStringLiteral("simulatorButton"));
        simulatorButton->setChecked(true);

        horizontalLayout->addWidget(simulatorButton);

        robotButton = new QRadioButton(frame_10);
        robotButton->setObjectName(QStringLiteral("robotButton"));

        horizontalLayout->addWidget(robotButton);


        verticalLayout->addWidget(frame_10);

        frame_13 = new QFrame(frame_2);
        frame_13->setObjectName(QStringLiteral("frame_13"));
        frame_13->setFrameShape(QFrame::StyledPanel);
        frame_13->setFrameShadow(QFrame::Raised);
        horizontalLayout_4 = new QHBoxLayout(frame_13);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        setTerrainButton = new QPushButton(frame_13);
        setTerrainButton->setObjectName(QStringLiteral("setTerrainButton"));

        horizontalLayout_4->addWidget(setTerrainButton);

        terrainFileLabel = new QLabel(frame_13);
        terrainFileLabel->setObjectName(QStringLiteral("terrainFileLabel"));

        horizontalLayout_4->addWidget(terrainFileLabel);


        verticalLayout->addWidget(frame_13);

        frame_14 = new QFrame(frame_2);
        frame_14->setObjectName(QStringLiteral("frame_14"));
        frame_14->setFrameShape(QFrame::StyledPanel);
        frame_14->setFrameShadow(QFrame::Raised);
        horizontalLayout_5 = new QHBoxLayout(frame_14);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        hide_floor_checkbox = new QCheckBox(frame_14);
        hide_floor_checkbox->setObjectName(QStringLiteral("hide_floor_checkbox"));

        horizontalLayout_5->addWidget(hide_floor_checkbox);

        hide_robot_checkbox = new QCheckBox(frame_14);
        hide_robot_checkbox->setObjectName(QStringLiteral("hide_robot_checkbox"));

        horizontalLayout_5->addWidget(hide_robot_checkbox);


        verticalLayout->addWidget(frame_14);

        label = new QLabel(frame_2);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout->addWidget(label);

        simulatorTable = new QTableWidget(frame_2);
        if (simulatorTable->columnCount() < 2)
            simulatorTable->setColumnCount(2);
        if (simulatorTable->rowCount() < 1)
            simulatorTable->setRowCount(1);
        simulatorTable->setObjectName(QStringLiteral("simulatorTable"));
        simulatorTable->setRowCount(1);
        simulatorTable->setColumnCount(2);
        simulatorTable->horizontalHeader()->setDefaultSectionSize(196);
        simulatorTable->verticalHeader()->setDefaultSectionSize(30);
        simulatorTable->verticalHeader()->setMinimumSectionSize(21);

        verticalLayout->addWidget(simulatorTable);

        frame_6 = new QFrame(frame_2);
        frame_6->setObjectName(QStringLiteral("frame_6"));
        frame_6->setFrameShape(QFrame::StyledPanel);
        frame_6->setFrameShadow(QFrame::Raised);
        gridLayout_3 = new QGridLayout(frame_6);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        loadSimulatorButton = new QPushButton(frame_6);
        loadSimulatorButton->setObjectName(QStringLiteral("loadSimulatorButton"));

        gridLayout_3->addWidget(loadSimulatorButton, 0, 1, 1, 1);

        saveSimulatorButton = new QPushButton(frame_6);
        saveSimulatorButton->setObjectName(QStringLiteral("saveSimulatorButton"));

        gridLayout_3->addWidget(saveSimulatorButton, 0, 0, 1, 1);


        verticalLayout->addWidget(frame_6);


        horizontalLayout_3->addWidget(frame_2);

        frame_5 = new QFrame(centralWidget);
        frame_5->setObjectName(QStringLiteral("frame_5"));
        frame_5->setFrameShape(QFrame::StyledPanel);
        frame_5->setFrameShadow(QFrame::Raised);
        verticalLayout_3 = new QVBoxLayout(frame_5);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        label_2 = new QLabel(frame_5);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout_3->addWidget(label_2);

        robotTable = new QTableWidget(frame_5);
        if (robotTable->columnCount() < 2)
            robotTable->setColumnCount(2);
        if (robotTable->rowCount() < 1)
            robotTable->setRowCount(1);
        robotTable->setObjectName(QStringLiteral("robotTable"));
        robotTable->setRowCount(1);
        robotTable->setColumnCount(2);
        robotTable->horizontalHeader()->setDefaultSectionSize(196);

        verticalLayout_3->addWidget(robotTable);

        frame_4 = new QFrame(frame_5);
        frame_4->setObjectName(QStringLiteral("frame_4"));
        frame_4->setFrameShape(QFrame::StyledPanel);
        frame_4->setFrameShadow(QFrame::Raised);
        gridLayout_2 = new QGridLayout(frame_4);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        loadRobotButton = new QPushButton(frame_4);
        loadRobotButton->setObjectName(QStringLiteral("loadRobotButton"));

        gridLayout_2->addWidget(loadRobotButton, 0, 1, 1, 1);

        saveRobotButton = new QPushButton(frame_4);
        saveRobotButton->setObjectName(QStringLiteral("saveRobotButton"));

        gridLayout_2->addWidget(saveRobotButton, 0, 0, 1, 1);


        verticalLayout_3->addWidget(frame_4);

        frame_12 = new QFrame(frame_5);
        frame_12->setObjectName(QStringLiteral("frame_12"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(frame_12->sizePolicy().hasHeightForWidth());
        frame_12->setSizePolicy(sizePolicy);
        frame_12->setFrameShape(QFrame::StyledPanel);
        frame_12->setFrameShadow(QFrame::Raised);
        gridLayout_6 = new QGridLayout(frame_12);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        frame_11 = new QFrame(frame_12);
        frame_11->setObjectName(QStringLiteral("frame_11"));
        frame_11->setFrameShape(QFrame::StyledPanel);
        frame_11->setFrameShadow(QFrame::Raised);
        verticalLayout_6 = new QVBoxLayout(frame_11);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        kickAngularX = new QLineEdit(frame_11);
        kickAngularX->setObjectName(QStringLiteral("kickAngularX"));
        QSizePolicy sizePolicy1(QSizePolicy::Ignored, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(kickAngularX->sizePolicy().hasHeightForWidth());
        kickAngularX->setSizePolicy(sizePolicy1);

        verticalLayout_6->addWidget(kickAngularX);

        kickAngularY = new QLineEdit(frame_11);
        kickAngularY->setObjectName(QStringLiteral("kickAngularY"));
        sizePolicy1.setHeightForWidth(kickAngularY->sizePolicy().hasHeightForWidth());
        kickAngularY->setSizePolicy(sizePolicy1);

        verticalLayout_6->addWidget(kickAngularY);

        kickAngularZ = new QLineEdit(frame_11);
        kickAngularZ->setObjectName(QStringLiteral("kickAngularZ"));
        sizePolicy1.setHeightForWidth(kickAngularZ->sizePolicy().hasHeightForWidth());
        kickAngularZ->setSizePolicy(sizePolicy1);

        verticalLayout_6->addWidget(kickAngularZ);

        kickLinearX = new QLineEdit(frame_11);
        kickLinearX->setObjectName(QStringLiteral("kickLinearX"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(kickLinearX->sizePolicy().hasHeightForWidth());
        kickLinearX->setSizePolicy(sizePolicy2);

        verticalLayout_6->addWidget(kickLinearX);

        kickLinearY = new QLineEdit(frame_11);
        kickLinearY->setObjectName(QStringLiteral("kickLinearY"));
        sizePolicy2.setHeightForWidth(kickLinearY->sizePolicy().hasHeightForWidth());
        kickLinearY->setSizePolicy(sizePolicy2);

        verticalLayout_6->addWidget(kickLinearY);

        kickLinearZ = new QLineEdit(frame_11);
        kickLinearZ->setObjectName(QStringLiteral("kickLinearZ"));
        sizePolicy2.setHeightForWidth(kickLinearZ->sizePolicy().hasHeightForWidth());
        kickLinearZ->setSizePolicy(sizePolicy2);

        verticalLayout_6->addWidget(kickLinearZ);


        gridLayout_6->addWidget(frame_11, 0, 0, 1, 1);

        kickButton = new QPushButton(frame_12);
        kickButton->setObjectName(QStringLiteral("kickButton"));

        gridLayout_6->addWidget(kickButton, 1, 0, 1, 1);


        verticalLayout_3->addWidget(frame_12);


        horizontalLayout_3->addWidget(frame_5);

        frame_3 = new QFrame(centralWidget);
        frame_3->setObjectName(QStringLiteral("frame_3"));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        verticalLayout_2 = new QVBoxLayout(frame_3);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label_3 = new QLabel(frame_3);
        label_3->setObjectName(QStringLiteral("label_3"));

        verticalLayout_2->addWidget(label_3);

        userControlTable = new QTableWidget(frame_3);
        if (userControlTable->columnCount() < 2)
            userControlTable->setColumnCount(2);
        if (userControlTable->rowCount() < 1)
            userControlTable->setRowCount(1);
        userControlTable->setObjectName(QStringLiteral("userControlTable"));
        userControlTable->setRowCount(1);
        userControlTable->setColumnCount(2);
        userControlTable->horizontalHeader()->setDefaultSectionSize(196);

        verticalLayout_2->addWidget(userControlTable);

        frame_7 = new QFrame(frame_3);
        frame_7->setObjectName(QStringLiteral("frame_7"));
        frame_7->setFrameShape(QFrame::StyledPanel);
        frame_7->setFrameShadow(QFrame::Raised);
        gridLayout_4 = new QGridLayout(frame_7);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        loadUserButton = new QPushButton(frame_7);
        loadUserButton->setObjectName(QStringLiteral("loadUserButton"));

        gridLayout_4->addWidget(loadUserButton, 0, 1, 1, 1);

        saveUserButton = new QPushButton(frame_7);
        saveUserButton->setObjectName(QStringLiteral("saveUserButton"));

        gridLayout_4->addWidget(saveUserButton, 0, 0, 1, 1);


        verticalLayout_2->addWidget(frame_7);

        frame_8 = new QFrame(frame_3);
        frame_8->setObjectName(QStringLiteral("frame_8"));
        frame_8->setFrameShape(QFrame::StyledPanel);
        frame_8->setFrameShadow(QFrame::Raised);
        verticalLayout_4 = new QVBoxLayout(frame_8);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        goHomeButton = new QPushButton(frame_8);
        goHomeButton->setObjectName(QStringLiteral("goHomeButton"));

        verticalLayout_4->addWidget(goHomeButton);


        verticalLayout_2->addWidget(frame_8);


        horizontalLayout_3->addWidget(frame_3);

        SimControlPanel->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(SimControlPanel);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1312, 28));
        SimControlPanel->setMenuBar(menuBar);
        mainToolBar = new QToolBar(SimControlPanel);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        SimControlPanel->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(SimControlPanel);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        SimControlPanel->setStatusBar(statusBar);

        retranslateUi(SimControlPanel);

        QMetaObject::connectSlotsByName(SimControlPanel);
    } // setupUi

    void retranslateUi(QMainWindow *SimControlPanel)
    {
        SimControlPanel->setWindowTitle(QApplication::translate("SimControlPanel", "SimControlPanel", nullptr));
        simulatorStateLabel->setText(QApplication::translate("SimControlPanel", "Simulator State: X", nullptr));
        simulatorConnectedLabel->setText(QApplication::translate("SimControlPanel", "Sim Connected?: X", nullptr));
        startButton->setText(QApplication::translate("SimControlPanel", "Start", nullptr));
        driverButton->setText(QApplication::translate("SimControlPanel", "Driver", nullptr));
        joystickButton->setText(QApplication::translate("SimControlPanel", "Joystick", nullptr));
        stopButton->setText(QApplication::translate("SimControlPanel", "Stop", nullptr));
        MilabButton->setText(QApplication::translate("SimControlPanel", "Milab", nullptr));
        cheetah3Button->setText(QApplication::translate("SimControlPanel", "Cheetah 3", nullptr));
        miniCheetahButton->setText(QApplication::translate("SimControlPanel", "Mini Cheetah", nullptr));
        simulatorButton->setText(QApplication::translate("SimControlPanel", "Simulator", nullptr));
        robotButton->setText(QApplication::translate("SimControlPanel", "Robot", nullptr));
        setTerrainButton->setText(QApplication::translate("SimControlPanel", "Set Terrain File", nullptr));
        terrainFileLabel->setText(QApplication::translate("SimControlPanel", "TextLabel", nullptr));
        hide_floor_checkbox->setText(QApplication::translate("SimControlPanel", "Hide Floor", nullptr));
        hide_robot_checkbox->setText(QApplication::translate("SimControlPanel", "Hide Simulated Robot", nullptr));
        label->setText(QApplication::translate("SimControlPanel", "Simulator Control Parameters", nullptr));
        loadSimulatorButton->setText(QApplication::translate("SimControlPanel", "Load", nullptr));
        saveSimulatorButton->setText(QApplication::translate("SimControlPanel", "Save", nullptr));
        label_2->setText(QApplication::translate("SimControlPanel", "Robot Control Parameters", nullptr));
        loadRobotButton->setText(QApplication::translate("SimControlPanel", "Load", nullptr));
        saveRobotButton->setText(QApplication::translate("SimControlPanel", "Save", nullptr));
        kickAngularX->setText(QApplication::translate("SimControlPanel", "0", nullptr));
        kickAngularY->setText(QApplication::translate("SimControlPanel", "0", nullptr));
        kickAngularZ->setText(QApplication::translate("SimControlPanel", "0", nullptr));
        kickLinearX->setText(QApplication::translate("SimControlPanel", "0", nullptr));
        kickLinearY->setText(QApplication::translate("SimControlPanel", "0", nullptr));
        kickLinearZ->setText(QApplication::translate("SimControlPanel", "0", nullptr));
        kickButton->setText(QApplication::translate("SimControlPanel", "Kick", nullptr));
        label_3->setText(QApplication::translate("SimControlPanel", "User Control Parameters", nullptr));
        loadUserButton->setText(QApplication::translate("SimControlPanel", "Load", nullptr));
        saveUserButton->setText(QApplication::translate("SimControlPanel", "Save", nullptr));
        goHomeButton->setText(QApplication::translate("SimControlPanel", "Go Home", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SimControlPanel: public Ui_SimControlPanel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIMCONTROLPANEL_H
