#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QFileDialog>
#include <QMessageBox>
#include <QComboBox>
#include <QStorageInfo>
#include <QDebug>
#include <QtGlobal>
#include <QTimer>


void RefreshDrives(QComboBox *combo_box) {
    combo_box->clear();
    QList<QStorageInfo> volumes = QStorageInfo::mountedVolumes();

    for (const QStorageInfo &volume : volumes) {
        if (volume.isValid() && volume.isReady()) {
            QString FileType = volume.fileSystemType().toLower();
            if (FileType == "vfat" || FileType == "exfat" && FileType == "fat32") {
                combo_box->addItem(volume.displayName());
            }
        }
    }
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QWidget window;
    window.setWindowTitle("Iso Installer");
    window.resize(800, 200);
    window.setFixedSize(800, 200);

    QPushButton *StartButton = new QPushButton("Start", &window);
    StartButton->setGeometry(20, 20, 100, 30);

    QPushButton *FileButton = new QPushButton("Choose file", &window);
    FileButton->setGeometry(680, 20, 100, 30);

    QObject::connect(FileButton, &QPushButton::clicked, [FileButton, &window]() {
        QString fileName = QFileDialog::getOpenFileName(&window,"Wybierz plik ISO: ",
            "",
            "Obraz ISO (*.iso);;Wszystkie pliki (*)");

        if (!fileName.isEmpty()) {
            if (fileName.toLower().endsWith(".iso")) {
                QString shortName = QFileInfo(fileName).fileName();
                FileButton->setText(shortName);
            } else {
                QMessageBox::warning(&window, "Blad", "Wybrany plik nie ma rozszerzenia .iso");
            }
        }
    });

    QComboBox *FileCombo = new QComboBox(&window);
    FileCombo->setGeometry(300, 120, 200, 30);

    RefreshDrives(FileCombo);
    QTimer *timer = new QTimer(&window);
    QObject::connect(timer, &QTimer::timeout, [&]() {
        RefreshDrives(FileCombo);
    });
    timer->start(1000);

    window.show();
    return app.exec();;
}