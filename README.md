# Betriebssysteme

IDE der Wahl benutzen, wie bei Windows Visual Studio Console Application und Code hinzufügen

## Library installieren (bei #include <phread.h> Problemen):
https://vcpkg.io/en/getting-started.html
1. Command Shell öffnen
2. Zum gewünschten Ordner navigieren und einfügen:
3. git clone https://github.com/Microsoft/vcpkg.git
4. .\vcpkg\bootstrap-vcpkg.bat
5. cd vcpkg
6. vcpkg install pthreads:x86-windows
7. vcpkg integrate install
8. Visual Studio neustarten
