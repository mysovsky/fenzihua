#include <iostream>
#include <QApplication>
#include <QStyleFactory>
#include <QFontDatabase>
#include <qppcad/ui/main_window.hpp>
#include <qppcad/app_state.hpp>
#include <QTextStream>
#include <QCommandLineParser>

using namespace qpp;
using namespace qpp::cad;

int main (int argc, char **argv) {
  std::ios_base::sync_with_stdio(false);

  QCoreApplication::setOrganizationName("igc");
  QCoreApplication::setOrganizationDomain("igc.irk.ru");
  QCoreApplication::setApplicationName("qppcad");
  QApplication app(argc, argv);

  QCommandLineParser parser;
  parser.setApplicationDescription("qpp::cad");
  parser.addHelpOption();
  parser.addVersionOption();
  parser.addPositionalArgument("file", "The file to open.");

  QCommandLineOption target_fmt_option(QStringList() << "f" << "format",
                                       QCoreApplication::translate("main", "Force file format"),
                                       QCoreApplication::translate("main", "file_format"));
  parser.addOption(target_fmt_option);

  parser.process(QCoreApplication::arguments());
  const QStringList args = parser.positionalArguments();


  app_state_t::init_inst();

  app_state_t *astate = app_state_t::get_inst();
  astate->init_managers();
  astate->ws_manager->init_ws_item_bhv_mgr();
  astate->ws_manager->init_default();
  astate->load_settings();

  if (!args.empty()) {

      std::string file_name = args[0].toStdString();
      std::string file_format = "";

      if (parser.isSet(target_fmt_option))
        file_format = parser.value(target_fmt_option).toStdString();

      astate->ws_manager->load_from_file_autodeduce(file_name, file_format);

    }

  QSurfaceFormat format;
  format.setDepthBufferSize(24);

  //format.setStencilBufferSize(8);
  format.setSamples(6);
  format.setVersion(3, 3);
  format.setProfile(QSurfaceFormat::CoreProfile);
  QSurfaceFormat::setDefaultFormat(format);

  qApp->setStyle(QStyleFactory::create("Fusion"));

  QPalette darkPalette;
  darkPalette.setColor(QPalette::Window,QColor(68,68,68));
  darkPalette.setColor(QPalette::WindowText,Qt::white);
  darkPalette.setColor(QPalette::Disabled,QPalette::WindowText,QColor(87,87,87));
  darkPalette.setColor(QPalette::Base,QColor(52,52,52));
  darkPalette.setColor(QPalette::AlternateBase,QColor(66,66,66));
  darkPalette.setColor(QPalette::ToolTipBase,Qt::white);
  darkPalette.setColor(QPalette::ToolTipText,Qt::white);
  darkPalette.setColor(QPalette::Text,Qt::white);
  darkPalette.setColor(QPalette::Disabled,QPalette::Text,QColor(97,97,97));
  darkPalette.setColor(QPalette::Dark,QColor(45,45,45));
  darkPalette.setColor(QPalette::Shadow,QColor(20,20,20));
  darkPalette.setColor(QPalette::Button,QColor(53,53,53));
  darkPalette.setColor(QPalette::ButtonText,Qt::white);
  darkPalette.setColor(QPalette::Disabled,QPalette::ButtonText,QColor(127,127,127));
  darkPalette.setColor(QPalette::BrightText,Qt::red);
  darkPalette.setColor(QPalette::Link,QColor(42,130,218));
  darkPalette.setColor(QPalette::Highlight,QColor(42,130,218));
  darkPalette.setColor(QPalette::Disabled,QPalette::Highlight,QColor(50,50,50));
  darkPalette.setColor(QPalette::HighlightedText,Qt::white);
  darkPalette.setColor(QPalette::Disabled,QPalette::HighlightedText,QColor(127,127,127));

  qApp->setPalette(darkPalette);
//  QFontDatabase::addApplicationFont("://fonts/Hack-Regular.ttf");
//  QFontDatabase::addApplicationFont("://fonts/Hack-Bold.ttf");

  QFontDatabase::addApplicationFont("://fonts/Open_Sans/OpenSans-Light.ttf");
  QFontDatabase::addApplicationFont("://fonts/Open_Sans/OpenSans-Bold.ttf");

  astate->m_font_name = "OpenSans";

  QFont font = QFont(astate->m_font_name, 12, 1);
  QIcon icon("://images/icon.svg");
  //QFont defaultFont = QApplication::font();
  font.setPointSize(font.pointSize());
  //qApp->setFont(defaultFont);
  app.setWindowIcon(icon);
  app.setFont(font);

  QFile file("://style.qss");
  file.open(QFile::ReadOnly);
  QString style_sheet = QLatin1String(file.readAll());
  app.setStyleSheet(style_sheet);

  main_window w;
  w.rebuild_recent_files_menu();
  w.showMaximized();
  int ret_code = app.exec();

  app_state_t::get_inst()->save_settings();

  return ret_code;

}
