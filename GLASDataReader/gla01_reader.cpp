#include "gla01_reader.h"
#include <QString>
#include <QTextStream>
#include <QDataStream>
#include <QFile>
gla01_reader::gla01_reader()
{
}

void gla01_reader::test()
{
    QString path="I:\\GLAS\\GLAS\\GLA01.033\\2003.02.20\\GLA01_033_1102_001_0071_4_01_0001.DAT";
    QFile ifile(path);
    if(!ifile.open(QIODevice::ReadOnly))
        return;
    QTextStream ts(&ifile);
    int blockLength;
    int headSize;
    QString reclStr=ts.readLine();
    QString numheadStr=ts.readLine();
    reclStr.remove(';');
    numheadStr.remove(';');
    blockLength=reclStr.mid(reclStr.lastIndexOf("=")+1).toInt();
    headSize=numheadStr.mid(numheadStr.lastIndexOf("=")+1).toInt();
    ifile.seek(blockLength*headSize);
    qint32 i_rec_ndx;
    qint32 i_UTCTime[2];
    qint16 i_gla01_rectype;
    while(!ifile.atEnd())
    {
        QByteArray buf=ifile.read(blockLength);
        QDataStream ifs(buf);
        ifs>>i_rec_ndx>>i_UTCTime[0]>>i_UTCTime[1]>>i_gla01_rectype;
        switch(i_gla01_rectype)
        {
        case 1://MAIN
            readMainRecord(ifs,i_rec_ndx,i_UTCTime);
            break;
        case 2://LONG
            readLongRecord(ifs,i_rec_ndx,i_UTCTime);
            break;
        case 3://SHORT
            readShortRecord(ifs,i_rec_ndx,i_UTCTime);
            break;
        }
    }

    ifile.close();
}

void gla01_reader::readMainRecord(QDataStream &ifs, qint32 rec_ndx, qint32 *utcTime)
{
    _GLA01_MAIN record;
    record.i_rec_ndx=rec_ndx;
    memcpy(record.i_UTCTime,utcTime,2*sizeof(qint32));
    record.i_gla01_rectype=1;
    ifs>>record.i_spare1;
    for(int i=0;i<39;++i)
        ifs>>record.i_dShotTime[i];
    ifs>>record.i1_pred_lat>>record.i1_pred_lon;
    for(int i=0;i<40;++i)
        ifs>>record.i_RespEndTime[i];
    for(int i=0;i<40;++i)
        ifs>>record.i_LastThrXingT[i];
    for(int i=0;i<40;++i)
        ifs>>record.i_NextThrXing[i];
    for(int i=0;i<40;++i)
        ifs>>record.i_EchoPeakLoc[i];
    for(int i=0;i<40;++i)
        ifs>>record.i_EchoPeakVal[i];
    for(int i=0;i<40;++i)
        for(int j=0;j<6;++j)
            ifs>>record.i_wt_fact_filt[i][j];
    for(int i=0;i<40;++i)
        ifs>>record.i_filtr_thresh[i];
    for(int i=0;i<40;++i)
        ifs>>record.i_time_txWfPk[i];
    for(int i=0;i<40;++i)
        ifs>>record.i_TxWfStart[i];
    ifs>>record.i_TxNrg_EU;
    for(int i=0;i<40;++i)
        ifs>>record.i_RecNrgAll_EU[i];
    for(int i=0;i<40;++i)
        ifs>>record.i_RecNrgLast_EU[i];
    for(int i=0;i<40;++i)
        ifs>>record.i_txWfPk_Flag[i];
    ifs>>record.i_InstState;
    for(int i=0;i<8;++i)
        ifs>>record.i_APID_AvFlg[i];
    ifs>>record.i_FiltNumMask;
    for(int i=0;i<2;++i)
        ifs>>record.i_HOff[i];
    for(int i=0;i<2;++i)
        ifs>>record.i_ADBias[i];
    for(int i=0;i<2;++i)
        ifs>>record.i_RminRmax[i];
    for(int i=0;i<2;++i)
        ifs>>record.i_WMinMax[i];
    ifs>>record.i_ObSCHt;
    for(int i=0;i<12;++i)
        ifs>>record.i_engineering[i];
    for(int i=0;i<2;++i)
        ifs>>record.i_compRatio[i];
    ifs>>record.i_N_val>>record.i_r_val>>record.i_ADdetOutGn>>record.i_DEMmin>>record.i_DEMmax;
    for(int i=0;i<40;++i)
        for(int j=0;j<48;++j)
            ifs>>record.i_tx_wf[i][j];
    for(int i=0;i<2;++i)
        ifs>>record.i_OrbFlg[i];
    ifs>>record.i_EchoLandType>>record.i_RngSrc_Flag>>record.i_timecorflg;
    for(int i=0;i<5;++i)
        ifs>>record.i_TxFlg[i];
    for(int i=0;i<5;++i)
        ifs>>record.i_GainShiftFlg[i];
    //DO SOMETHING
    writeToDB(record);
}

void gla01_reader::readLongRecord(QDataStream &ifs, qint32 rec_ndx, qint32 *utcTime)
{
    _GLA01_LONG record;
    record.i_rec_ndx=rec_ndx;
    memcpy(record.i_UTCTime,utcTime,2*sizeof(qint32));
    record.i_gla01_rectype=2;
    ifs>>record.i_spare1;
    for(int i=0;i<8;++i)
        ifs>>record.i_filtnum[i];
    for(int i=0;i<8;++i)
        ifs>>record.i_shot_ctr[i];
    for(int i=0;i<8;++i)
        ifs>>record.i_statflags[i];
    for(int i=0;i<8;++i)
        ifs>>record.i_gainSet1064[i];
    for(int i=0;i<8;++i)
        ifs>>record.i_4nsPeakVal[i];
    for(int i=0;i<8;++i)
        ifs>>record.i_8nsPeakVal[i];
    for(int i=0;i<8;++i)
        ifs>>record.i_4nsBgMean[i];
    for(int i=0;i<8;++i)
        ifs>>record.i_4nsBgSDEV[i];
    for(int i=0;i<8;++i)
        ifs>>record.i_samp_pad[i];
    for(int i=0;i<8;++i)
        ifs>>record.i_comp_type[i];
    for(int i=0;i<8;++i)
        for(int j=0;j<544;++j)
        ifs>>record.i_rng_wf[i][j];
    for(int i=0;i<8;++i)
        ifs>>record.i_gainStatus[i];
    for(int i=0;i<8;++i)
        ifs>>record.i_NumCoinc[i];
    for(int i=0;i<8;++i)
        ifs>>record.i_rawPkHt[i];
    //DO SOMETING
    writeToDB(record);
}

void gla01_reader::readShortRecord(QDataStream &ifs, qint32 rec_ndx, qint32 *utcTime)
{
    _GLA01_SHORT record;
    record.i_rec_ndx=rec_ndx;
    memcpy(record.i_UTCTime,utcTime,2*sizeof(qint32));
    record.i_gla01_rectype=3;
    ifs>>record.i_spare1;
    for(int i=0;i<20;++i)
        ifs>>record.i_filtnum[i];
    for(int i=0;i<20;++i)
        ifs>>record.i_shot_ctr[i];
    for(int i=0;i<20;++i)
        ifs>>record.i_statflags[i];
    for(int i=0;i<20;++i)
        ifs>>record.i_gainSet1064[i];
    for(int i=0;i<20;++i)
        ifs>>record.i_4nsPeakVal[i];
    for(int i=0;i<20;++i)
        ifs>>record.i_8nsPeakVal[i];
    for(int i=0;i<20;++i)
        ifs>>record.i_4nsBgMean[i];
    for(int i=0;i<20;++i)
        ifs>>record.i_4nsBgSDEV[i];
    for(int i=0;i<20;++i)
        ifs>>record.i_samp_pad[i];
    for(int i=0;i<20;++i)
        ifs>>record.i_comp_type[i];
    for(int i=0;i<20;++i)
        for(int j=0;j<200;++j)
        ifs>>record.i_rng_wf[i][j];
    for(int i=0;i<20;++i)
        ifs>>record.i_gainStatus[i];
    for(int i=0;i<20;++i)
        ifs>>record.i_NumCoinc[i];
    for(int i=0;i<20;++i)
        ifs>>record.i_rawPkHt[i];
    //DO SOMETHING
    writeToDB(record);
}

void gla01_reader::writeToDB(_GLA01_MAIN &record)
{
    query.exec
}

void gla01_reader::writeToDB(_GLA01_LONG &record)
{

}

void gla01_reader::writeToDB(_GLA01_SHORT &record)
{

}
