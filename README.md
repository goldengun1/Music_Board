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

### Linux (Ubuntu 22.04)

Za kompilaciju na Linux sistemima potrebni su sledeci paketi: `git gcc g++ cmake qtcreator qtbase5-dev qt5-qmake qtmultimedia5-dev`.

##### Koraci za kompilaciju na Ubuntu 22.04:

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

### Windows 10 (ili novije)

Neophodno je imati Qt Creator instaliran na podrazumevanoj lokaciji (`C:\Qt`).
Neophodno je imati Qt 5.15.2 alate za MSVC instalirane (verzija 2019) na podrazumevanoj lokaciji (`C:\Qt`).
Neophodno je imati ili [Build Tools for Visual Studio](https://visualstudio.microsoft.com/downloads/#build-tools-for-visual-studio-2019) ili [Visual Studio](https://visualstudio.microsoft.com/downloads/) instalirane na podrazumevanoj lokaciji.

##### Koraci za kompilaciju na Windows 10:

```bat
rem Otvoriti Qt Creator.
rem Pritisnuti "File", zatim "Open File or Project" i otvoriti CMakeLists.txt koji se nalazi na korenu projekta.
rem Kada se projekat otvori, pritisnuti "Build", zatim "Build All Project".
rem Pokretanje programa i testova se moze izvrsiti unutar Qt Creator.
```

##### Korazi za pravljenje konačne .zip datoteke (sa svim zavisnim datotekama):
```bat
rem Pokrenuti deploy.bat.
rem .zip se nalazi u direktorijumu iznad korena projekta.

rem Moguce je i sa command prompt uraditi isto (u korenu projekta):
call       deploy.bat

rem Detaljnije (rucno, polazni direktorijum je koren projekta):
rem (otvoriti cmd.exe u korenu projekta i uraditi copy i paste narednog koda)
pushd      .
set        deployqt=C:\Qt\5.15.2\msvc2019_64\bin\windeployqt.exe
set        deploydir=deploy
cd         ..
mkdir      %deploydir%
cd         build*release
set        releasedir=%cd%
cd         ..
copy       %releasedir%\05-muzicka-tabla.exe %deploydir%\
%deployqt% %deploydir%\05-muzicka-tabla.exe --no-translations
tar        -a -cf 05-muzicka-tabla.zip %deploydir%
popd
rem 05-muzicka-tabla.zip se nalazi u direktorijumu iznad korena projekta.
```

## Napomene

1. Ukoliko se radi na Windows operativnom sistemu, potrebno je u Qt Creator-u postaviti env promenljivu: `QT_MULTIMEDIA_PREFERRED_PLUGINS=windowsmediafoundation`

# Pregled

## Demo video: [Muzicka Tabla](https://youtu.be/AGG2Z7ID35c)

## Pictures:
![1](https://gitlab.com/matf-bg-ac-rs/course-rs/projects-2022-2023/05-muzicka-tabla/-/blob/ef4b9fddc4f777db691c5ce479a2e0c6f4f77c38/demo/demo_pic1.png)
![2](https://gitlab.com/matf-bg-ac-rs/course-rs/projects-2022-2023/05-muzicka-tabla/-/blob/ef4b9fddc4f777db691c5ce479a2e0c6f4f77c38/demo/demo_pic2.png)
![3](https://gitlab.com/matf-bg-ac-rs/course-rs/projects-2022-2023/05-muzicka-tabla/-/blob/ef4b9fddc4f777db691c5ce479a2e0c6f4f77c38/demo/demo_pic3.png)
