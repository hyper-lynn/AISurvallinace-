#ifndef TOKENCTRL_H
#define TOKENCTRL_H

#include <QObject>
#include "Src/Utils/global.h"

typedef struct tokenParameters
{
    QString     host;
    int         port;
    QString     appId;
    QString     appSecret;
    QString     phone;
}TOKEN_PARAMETERS;

typedef struct userBindParameters
{
    TOKEN_PARAMETERS info;
    //QString          smsCode;
}USERBIND_PARAMETERS;

class TokenCtrl : public QObject
{
    Q_OBJECT

public:
    TokenCtrl();
    ~TokenCtrl();

    static int getAccessToken(const TOKEN_PARAMETERS* param, OUT QString& token, OUT QString& ret_code, OUT QString& ret_msg);
    static int getUserToken(const TOKEN_PARAMETERS* param, OUT QString& token, OUT QString& ret_code, OUT QString& ret_msg);
    static int userBindSms(const TOKEN_PARAMETERS* param, OUT QString& ret_code, OUT QString& ret_msg);
    static int userBind(const USERBIND_PARAMETERS* param, OUT QString& ret_code, OUT QString& ret_msg);

};

#endif // TOKENCTRL_H
