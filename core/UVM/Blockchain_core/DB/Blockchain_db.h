//
// Created by Kirill Zhukov on 12.06.2022.
//

#ifndef UVM_BLOCKCHAIN_DB_H
#define UVM_BLOCKCHAIN_DB_H
#include "rocksdb/db.h"
#include "rocksdb/slice.h"
#include "rocksdb/options.h"
#include "cassert"
#include "vector"
#include "iterator"
#include "../../error_handling/Result.h"
#include "../Block.h"
#include "../Wallet/WalletAccount.h"
#include "../Token/Token.h"
/// utility structures
#if defined(OS_WIN)
#include <Windows.h>
    static std::string kDBPath = "C:\\Windows\\TEMP\\unit";
    const char DBPath[] = "C:\\Windows\\TEMP\\unit";
    SYSTEM_INFO system_info;
    GetSystemInfo(&system_info);
    const int cpus = (int) system_info.dwNumberOfProcessors;
#else
#include <unistd.h>
#include <thread>
static std::string kDBPath = "/Users/kirillzhukov/Documents/unit_db";
const char DBPath[] = "/Users/kirillzhukov/Documents/unit_db";
//    static std::string kDBPath = "/tmp/unit_db/";
//    const char DBPath[] = "/tmp/unit_db/";
const int cpus = (int) std::thread::hardware_concurrency();
#endif

#define UNIT_TRANSFER 0
#define CREATE_TOKEN 1


class Blockchain_db {
public:
    Result<bool> start_node_db();
    /* column families for blockchain database
     * blockTX - stores data about blocks
     * addressContracts maps contract address to total number of transactions, number of non contract transactions
     * tx - stores transactions
     * height - maps block height to block hash and additional data about block
     * accountBalance - stores balances of each user's address
     */
    const std::vector<rocksdb::ColumnFamilyDescriptor> columnFamilies = {rocksdb::ColumnFamilyDescriptor("blockTX", rocksdb::ColumnFamilyOptions()),
                                                                         rocksdb::ColumnFamilyDescriptor("addressContracts", rocksdb::ColumnFamilyOptions()),
                                                                         rocksdb::ColumnFamilyDescriptor("tx", rocksdb::ColumnFamilyOptions()),
                                                                         rocksdb::ColumnFamilyDescriptor("height", rocksdb::ColumnFamilyOptions()),
                                                                         rocksdb::ColumnFamilyDescriptor("accountBalance", rocksdb::ColumnFamilyOptions()),
                                                                         rocksdb::ColumnFamilyDescriptor(ROCKSDB_NAMESPACE::kDefaultColumnFamilyName, rocksdb::ColumnFamilyOptions())
    };
    const std::vector<std::string> columnFamiliesNames = {"blockTX", "addressContracts", "tx", "height", "accountBalance"};
    Result<bool> push_block(Block &block);
    Result<bool> push_transaction(Transaction &transaction);
    Result<bool> create_new_token(std::string &name, double supply, std::string &creator, std::string bytecode, Transaction &transaction);
};

#endif //UVM_BLOCKCHAIN_DB_H