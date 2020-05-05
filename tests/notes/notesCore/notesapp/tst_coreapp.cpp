#include <QtTest>
#include "serviceregistry.h"
#include "testapp.h"
#include "testviewmodel.h"
using namespace QtMvvm;

QTMVVM_REGISTER_CORE_APP(TestApp)

class CoreAppTest : public QObject
{
	Q_OBJECT

public:
	using MsgFn = std::function<void()>;

private Q_SLOTS:
	void initTestCase();

	void testAppBoot();
//	void testTypeMapping_data();
//	void testTypeMapping();

//	void testPresentVm();
//	void testPresentVmArgs();
//	void testPresentVmChild();
//	void testPresentVmForResult();
//	void testPresentVmContainer();
//	void testPresentVmSingleton();

//	void testPresentDialog();
//	void testPresentMessage_data();
//	void testPresentMessage();

Q_SIGNALS:
	void msgUnblock(bool success);

private:
	bool wasClosed = false;
	QPointer<ProgressControl> lastProgress;

	Q_INVOKABLE void doCloseTest();
};

Q_DECLARE_METATYPE(CoreAppTest::MsgFn)

void CoreAppTest::initTestCase()
{
	qRegisterMetaType<TestViewModel*>();
	qRegisterMetaType<TestSingleViewModel*>();
	qRegisterMetaType<MsgFn>("MsgFn");
	QtMvvm::ServiceRegistry::instance()->registerInterface<QtMvvm::IPresenter, TestPresenter>();
}

void CoreAppTest::testAppBoot()
{
	QVERIFY(coreApp);
	QVERIFY(coreApp->wasRegistered);
	QVERIFY(coreApp->startArgs.isEmpty());

	QSignalSpy startSpy{coreApp, &TestApp::appStarted};
	QCoreApplication::processEvents();
	QVERIFY(!coreApp->startArgs.isEmpty());
	QCOMPARE(coreApp->startArgs, QCoreApplication::arguments());
	QCOMPARE(startSpy.size(), 1);
}





void CoreAppTest::doCloseTest()
{
	wasClosed = true;
}

QTEST_MAIN(CoreAppTest)

#include "tst_coreapp.moc"
