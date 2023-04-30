#include "connectdialog.h"
#include "ui_connectdialog.h"

ConnectDialog::ConnectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnectDialog)
{
    ui->setupUi(this);
    QLabel *ipLabel = new QLabel(tr("IP Address:"));
    QLabel *portLabel = new QLabel(tr("Port Number:"));

    ipLineEdit = new QLineEdit;
    portLineEdit = new QLineEdit;
    portLineEdit->setValidator(new QIntValidator(1, 65535, this));

    blackRadio = new QRadioButton(tr("Hold Black"));
    whiteRadio = new QRadioButton(tr("Hold White"));
    colorGroup = new QButtonGroup(this);
    colorGroup->addButton(blackRadio);
    colorGroup->addButton(whiteRadio);

    //connectButton = new QPushButton(tr("Connect"));

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(ipLabel, 0, 0);
    layout->addWidget(ipLineEdit, 0, 1);
    layout->addWidget(portLabel, 1, 0);
    layout->addWidget(portLineEdit, 1, 1);
    layout->addWidget(blackRadio, 2, 0);
    layout->addWidget(whiteRadio, 2, 1);
    //layout->addWidget(connectButton, 3, 0, 1, 2);
    setLayout(layout);
}

ConnectDialog::~ConnectDialog()
{
    delete ui;
}

void ConnectDialog::on_pushButton_clicked()
{
    ip = ipLineEdit->text();
    port = portLineEdit->text().toInt();
    online_hold = blackRadio->isChecked();

    this->close();
}

QString ConnectDialog::get_ip() const
{
    return ip;
}

quint16 ConnectDialog::get_port() const
{
    return port;
}

bool ConnectDialog::get_hold() const
{
    return online_hold;
}
