# Muzicka tabla

Aplikacija koja nam omogućava da učitavamo, snimimo, manipulisemo i reprodukujemo zvuk.

<ul>
    <li><a href="https://gitlab.com/ljubauros">Uroš Ljubisavljević 425/2019</a></li>
    <li><a href="https://gitlab.com/tamtung">Todor Todorović 241/2019</a></li>
    <li><a href="https://gitlab.com/penReptiloid">Aleksandar Urošević 201/2019</a></li>
    <li><a href="https://gitlab.com/_astevic">Aleksa Stević 37/2018</a></li>
    <li><a href="https://gitlab.com/mihailo.simic">Mihailo Simić 267/2018</a></li>
</ul>

## Kompilacija

Za kompilaciju na Linux sistemima potrebni su sledeci paketi: `git gcc g++ cmake qtcreator qtbase5-dev qt5-qmake qtmultimedia5-dev`.

Koraci za kompilaciju na Ubuntu 22.04:

```sh
sudo apt install -y git gcc g++ cmake qtcreator qtbase5-dev qt5-qmake qtmultimedia5-dev
git clone https://gitlab.com/matf-bg-ac-rs/course-rs/projects-2022-2023/05-muzicka-tabla
cd 05-muzicka-tabla
mkdir build
cd build
cmake ..
make

# Za pokretanje programa (u build direktorijumu):
./05-muzicka-tabla

# Za pokretanje testova (u build direktorijumu):
./tests/tests
```

## Napomene

1. Ukoliko se radi na Windows operativnom sistemu, potrebno je u Qt Creator-u postaviti env promenljivu: `QT_MULTIMEDIA_PREFERRED_PLUGINS=windowsmediafoundation`
