#include <QDir>
#include <QFile>
#include <QMainWindow>

#include "settings.h"


namespace HEHUI {

Settings::Settings(const QString fileBaseName, const QString fileDirPath, QObject* parent )
        : SettingsBase(fileBaseName, fileDirPath, parent )
{

	//beginGroup( mProgramVersion );
}

Settings::~Settings()
{
	//endGroup();


}









} //namespace HEHUI

