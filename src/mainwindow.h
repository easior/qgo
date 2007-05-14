/***************************************************************************
* Mainwindow.h
* headers for the main client window           *
 ***************************************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"
#include "mainwindow_settings.h"
#include "globals.h"
#include "sgfparser.h"
#include "boardwindow.h"
#include "igsconnection.h"
#include "parser.h"
#include "qgo_interface.h"

#include <QtGui>

class HostList;


class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow( QWidget *parent = 0 , Qt::WindowFlags flags = 0 );
	~MainWindow();

	int sendTextFromApp(const QString&, bool localecho=true);
	void sendcommand(const QString&, bool localecho=false);
	void set_sessionparameter(QString, bool);

public slots:
	// sfg slots
	void slot_fileNewBoard();
	void slot_fileOpenBoard();
	void slot_displayFileHeader(const QModelIndex & topLeft, const QModelIndex & bottomRight );
	
	// go engine slots
	void slot_computerNewBoard();
	void slot_computerOpenBoard();
	void slot_loadComputerFile(const QModelIndex & topLeft, const QModelIndex & bottomRight );

	//preferences tabs slots
	void slot_addServer();
	void slot_clickedListView(QTreeWidgetItem *lvi ,  int i);
	void slot_new();
	void slot_serverChanged( const QString &server);

	// server slots
	void slot_connect(bool b);
	void slot_textReceived(const QString &txt);
	void slot_message(QString, QColor = Qt::black);
//	void slot_message(QString txt);
	void set_tn_ready();
	void slot_sendCommand(const QString &, bool);
//	void slot_cmdactivated_int(int);
	void slot_cmdactivated(const QString&);

	// parser slots
	void slot_refresh(int i);
	void slot_accname(QString &name);
	void slot_svname(GSName &gs);
	void slot_addSeekCondition(const QString& a, const QString& b, const QString& c, const QString& d, const QString& );
	void slot_room(const QString& room, bool b);
	void slot_game(Game* g);
	void slot_player(Player *p, bool cmdplayers);

	void slot_sortGames (int);
	void slot_sortPlayers (int);
	void slot_gamesDoubleClicked(QTreeWidgetItem* lv);

protected:
	void closeEvent(QCloseEvent *e);
	void loadSettings();
	void saveSettings();

private:
	Ui::MainWindow ui;
	QDirModel *model;
	SGFParser * MW_SGFparser;
	QString SGFloaded, SGFloaded2, fileLoaded , fileLoaded2 ;
	GameData * GameLoaded , * GameLoaded2 ;
	qGoIF * qgoif;

//	QList<BoardWindow *> boardList;
	void createGame(GameMode gameMode, GameData * gameData, bool myColorIsBlack = FALSE, bool myColorIsWhite = FALSE, QString fileLoaded = "");


	// online time
	int                onlineCount;
	bool               youhavemsg;
	bool               playerListEmpty;
	bool               playerListSteadyUpdate;
	bool               gamesListSteadyUpdate;
//	bool               gamesListEmpty;
	bool               autoAwayMessage;

	// cmd_xx get current cmd number, and, if higher than last, cmd is valid,
	//    else cmd is from history list
	int		cmd_count;
	bool		cmd_valid;
	// telnet ready
	bool		tn_ready;
	bool		tn_wait_for_tn_ready;
	HostList 	hostlist;
	IGSConnection 	*igsConnection;

	QList<sendBuf*>  sendBuffer;
	sendBuf		*currentCommand;
	Account		*myAccount;
	Parser		*parser;
	QMenu 		*seekMenu;

	//players table
	void showOpen(bool show);
	void prepareTables(InfoType cmd);
	void setColumnsForExtUserInfo();
	QString rkToKey(QString txt, bool integer=FALSE);
};

#endif


