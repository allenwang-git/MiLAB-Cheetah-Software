/********************************************************************************
** Form generated from reading UI file 'JoystickTest.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_JOYSTICKTEST_H
#define UI_JOYSTICKTEST_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_JoystickTestWindow
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *leftXLabel;
    QLabel *leftYLabel;
    QLabel *rightXLabel;
    QLabel *rightYLabel;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *JoystickTestWindow)
    {
        if (JoystickTestWindow->objectName().isEmpty())
            JoystickTestWindow->setObjectName(QStringLiteral("JoystickTestWindow"));
        JoystickTestWindow->resize(400, 300);
        verticalLayout = new QVBoxLayout(JoystickTestWindow);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        leftXLabel = new QLabel(JoystickTestWindow);
        leftXLabel->setObjectName(QStringLiteral("leftXLabel"));

        verticalLayout->addWidget(leftXLabel);

        leftYLabel = new QLabel(JoystickTestWindow);
        leftYLabel->setObjectName(QStringLiteral("leftYLabel"));

        verticalLayout->addWidget(leftYLabel);

        rightXLabel = new QLabel(JoystickTestWindow);
        rightXLabel->setObjectName(QStringLiteral("rightXLabel"));

        verticalLayout->addWidget(rightXLabel);

        rightYLabel = new QLabel(JoystickTestWindow);
        rightYLabel->setObjectName(QStringLiteral("rightYLabel"));

        verticalLayout->addWidget(rightYLabel);

        buttonBox = new QDialogButtonBox(JoystickTestWindow);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(JoystickTestWindow);
        QObject::connect(buttonBox, SIGNAL(accepted()), JoystickTestWindow, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), JoystickTestWindow, SLOT(reject()));

        QMetaObject::connectSlotsByName(JoystickTestWindow);
    } // setupUi

    void retranslateUi(QDialog *JoystickTestWindow)
    {
        JoystickTestWindow->setWindowTitle(QApplication::translate("JoystickTestWindow", "Joystick Test", nullptr));
        leftXLabel->setText(QApplication::translate("JoystickTestWindow", "Left X:", nullptr));
        leftYLabel->setText(QApplication::translate("JoystickTestWindow", "Left Y:", nullptr));
        rightXLabel->setText(QApplication::translate("JoystickTestWindow", "Right X:", nullptr));
        rightYLabel->setText(QApplication::translate("JoystickTestWindow", "Right Y:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class JoystickTestWindow: public Ui_JoystickTestWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_JOYSTICKTEST_H
