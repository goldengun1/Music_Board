#pragma once

#include <QObject>

class MatrixPlayer: public QObject {
    Q_OBJECT

public:
    explicit MatrixPlayer(QObject *parent = nullptr);
    void PlayMatrix();
};
