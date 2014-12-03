#ifndef GLA01_READER_H
#define GLA01_READER_H

#include <QDataStream>
#include <QSqlDatabase>

class _GLA01_MAIN
{
public:
    qint32 i_rec_ndx;    //GLAS record index
    qint32 i_UTCTime[2];    //Transmit time of first shot in frame in J2000 (referenced from noon on 01 January 2000)
    qint16 i_gla01_rectype;    //GLA01 record type
    qint16 i_spare1;    //Spares
    qint32 i_dShotTime[39];    //Laser shot deltas (shots 2-40)
    qint32 i1_pred_lat;    //Predicted geodetic latitude of the laser footprint
    qint32 i1_pred_lon;    //Predicted geodetic qint32itude of the laser footprint
    qint32 i_RespEndTime[40];    //Ending address of range reponse
    qint32 i_LastThrXingT[40];    //Last threshold crossing location for selected filter
    qint32 i_NextThrXing[40];    //Next to last threshold crossing location for selected filter
    qint32 i_EchoPeakLoc[40];    //Echo peak location
    qint16 i_EchoPeakVal[40];    //Echo peak value
    qint32 i_wt_fact_filt[40][6];    //Filter weight factors
    qint16 i_filtr_thresh[40];    //Selected filter threshold value
    qint32 i_time_txWfPk[40];    //Transmit pulse peak location
    qint32 i_TxWfStart[40];    //Starting address of transmit pulse sample
    qint32 i_TxNrg_EU;    //1064 nm laser transmit energy
    qint32 i_RecNrgAll_EU[40];    //1064 nm laser received energy from all signals above threshold
    qint32 i_RecNrgLast_EU[40];    //1064 nm laser received energy
    qint8 i_txWfPk_Flag[40];    //Transmit waveform peak status flag (view byte structure)
    qint32 i_InstState;    //Instrument state
    qint8 i_APID_AvFlg[8];    //APID data availability flag
    qint32 i_FiltNumMask;    //Filter selection mask
    qint32 i_HOff[2];    //DEM offset
    qint32 i_ADBias[2];    //Altimeter digitizer bias
    qint32 i_RminRmax[2];    //Range window start and stop
    qint32 i_WMinMax[2];    //Window size
    qint32 i_ObSCHt;    //Onboard height of spacecraft
    qint16 i_engineering[12];    //Engineering data
    qint16 i_compRatio[2];    //Compression ratios
    qint16 i_N_val;    //Value of N
    qint16 i_r_val;    //Value of r
    qint16 i_ADdetOutGn;    //Transmitted gain
    qint16 i_DEMmin;    //DEM minimum
    qint16 i_DEMmax;    //DEM maximum
    quint8 i_tx_wf[40][48];    //Sampled transmit pulse waveform
    qint8 i_OrbFlg[2];    //Orbit flag
    qint8 i_EchoLandType;    //Echo land type
    qint8 i_RngSrc_Flag;    //Range data source (view byte structure)
    qint16 i_timecorflg;    //Time correction flag
    qint8 i_TxFlg[5];    //Transmit pulse flag
    qint8 i_GainShiftFlg[5];    //Gain shift flag
    qint8 i_spare2[10];    //Spares
public:

};

class _GLA01_LONG
{
public:
    qint32 i_rec_ndx ;    //GLAS record index
    qint32 i_UTCTime[2];    //Transmit time of first shot in frame in J2000
    qint16 i_gla01_rectype;    //GLA01 record type
    qint16 i_spare1;    //Spares
    qint8 i_filtnum[8];    //Filter number
    qint16 i_shot_ctr[8];    //Shot counter
    qint32 i_statflags[8];    //Range window status word
    qint16 i_gainSet1064[8];    //AD gain setting
    qint16 i_4nsPeakVal[8];    //4 ns filter peak value
    qint16 i_8nsPeakVal[8];    //8 ns filter peak value
    quint16 i_4nsBgMean[8];    //Background mean value
    quint16 i_4nsBgSDEV[8];    //Background standard deviation
    qint16 i_samp_pad[8];    //Echo sample padding
    qint8 i_comp_type[8];    //Echo compression type
    quint8 i_rng_wf[8][544];    //1064 nm range waveform
    qint8 i_gainStatus[8];    //Gain status bits
    qint8 i_NumCoinc[8];    //Number of coincidences for selected filter
    qint8 i_rawPkHt[8];    //Height of peak in raw waveform
    qint8 i_spare2[108];    //Spares
public:
};

class _GLA01_SHORT
{
public:
    qint32 i_rec_ndx;    //GLAS record index
    qint32 i_UTCTime[2];    //Transmit time of first shot in frame in J2000
    qint16 i_gla01_rectype;    //GLA01 record type
    qint16 i_spare1;    //Spares
    qint8 i_filtnum[20];    //Filter number
    qint16 i_shot_ctr[20];    //Shot counter
    qint32 i_statflags[20];    //Range window status word
    qint16 i_gainSet1064[20];    //AD gain setting
    qint16 i_4nsPeakVal[20];    //4 ns filter peak value
    qint16 i_8nsPeakVal[20];    //8 ns filter peak value
    quint16 i_4nsBgMean[20];    //Background mean value
    quint16 i_4nsBgSDEV[20];    //Background standard deviation
    qint16 i_samp_pad[20];    //Echo sample padding
    qint8 i_comp_type[20];    //Echo compression type
    quint8 i_rng_wf[20][200];    //1064 nm range waveform
    qint8 i_gainStatus[20];    //Gain status bits
    qint8 i_NumCoinc[20];    //Number of coincidences for selected filter
    qint8 i_rawPkHt[20];    //Height of peak in raw waveform
    qint8 i_spare2[184];    //Spares
public:

};

class gla01_reader
{
public:
    gla01_reader();
    bool setupDB(QString host,QString dbName,QString user,QString pwd)
    {
        if(db.isOpen())
            db.close();
        db=QSqlDatabase::addDatabase("QODBC");
        db.setDatabaseName(QString("DRIVER={SQL SERVER};"
                                   "SERVER=%1;" //服务器名称
                                   "DATABASE=%2;"//数据库名
                                   "UID=%3;"           //登录名
                                   "PWD=%4;"        //密码
                                   ).arg(host)
                                    .arg(dbName)
                                    .arg(user)
                                    .arg(pwd));
        return db.open();
    }
    void test();
private:
    void readMainRecord(QDataStream& ifs, qint32 rec_ndx, qint32 *utcTime);
    void readLongRecord(QDataStream& ifs, qint32 rec_ndx, qint32 *utcTime);
    void readShortRecord(QDataStream& ifs, qint32 rec_ndx, qint32 *utcTime);

    void writeToDB(_GLA01_MAIN& record);
    void writeToDB(_GLA01_LONG& record);
    void writeToDB(_GLA01_SHORT& record);
private:
    QSqlDatabase db;
    QSqlQuery query;
};

#endif // GLA01_READER_H
