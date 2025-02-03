#include <QApplication>
#include "mainwindow.h"

/**
 * @brief Application entry point
 * @param argc Command-line argument count
 * @param argv Command-line argument values
 * @return Application exit code
 * 
 * Initializes Qt application and main window, then starts event loop.
 */
int main(int argc, char *argv[]) {
    // Create Qt application instance (required for GUI apps)
    QApplication app(argc, argv);
    
    // Create and display main window
    MainWindow window;
    window.show();  // Make window visible
    
    // Start Qt event loop (blocks until application exits)
    return app.exec();
}