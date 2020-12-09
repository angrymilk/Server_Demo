#include "DemoClient.h"

int main(int argc, char **argv)
{
    if (argc < 5)
    {
        printf("Input:srcip srcport dstip dstport\n");
        return 0;
    }
    ClientInfo cInfo = {string(argv[1]), atoi(argv[2]), 10024};
    ServerInfo sInfo = {string(argv[3]), atoi(argv[4])};
    shared_ptr<DemoClient> ptr(new DemoClient(cInfo, sInfo));
    ptr->working();
    return 0;
}

/*
INSERT INTO PlayerInfo(port, ip) VALUES(3000, "127.0.0.1", )

    alter table PlayerInfo add user_ip varchar(30);
    alter table PlayerInfo change ip_address user_ip varchar(30); 
    alter table PlayerInfo change uid user_id column specifications and constraints;

UPDATE PlayerInfo SET user_id=6989 where user_name="chenzun";
    */