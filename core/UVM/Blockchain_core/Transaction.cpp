//
// Created by Kirill Zhukov on 10.06.2022.
//

#include <string>
#include <map>
#include "Transaction.h"
#include "Crypto/kec256.h"

Transaction::Transaction() {}

Transaction::~Transaction() {}

const std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char>> &
Transaction::getFrom() const {
    return this->from;
}

void
Transaction::setFrom(const std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char>> &from) {
    this->from = from;
}

const std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char>> &Transaction::getTo() const {
    return this->to;
}

void
Transaction::setTo(const std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char>> &to) {
    this->to = to;
}

uint64_t Transaction::getType() const {
    return this->type;
}

void Transaction::setType(uint64_t type) {
    this->type = type;
}

uint64_t Transaction::getDate() const {
    return this->date;
}

void Transaction::setDate(uint64_t date) {
    this->date = date;
}

const std::__1::map<std::string, std::string> &Transaction::getExtraData() const {
    return this->extra_data;
}

void Transaction::setExtraData(const std::__1::map<std::string, std::string> &extraData) {
    this->extra_data = extraData;
}

void Transaction::generate_tx_hash() {
    std::string tx_as_str = this->to_string();
    std::string tx_hash = kec256::getHash(tx_as_str, tx_as_str.length());
    this->hash = kec256::getHash(tx_hash, tx_hash.length());
}

std::ostream &operator<<(std::ostream &out, const Transaction &transaction) {
    std::map<std::string, std::string> extra_map = transaction.extra_data;
    return out << "{\"" << transaction.from << "\", \"" << transaction.to << "\", " << transaction.type << ", " << transaction.date << ", \"" << extra_map["name"] << "\", \"" << extra_map["value"] << "\", \"" << transaction.previous_hash << "\", " << transaction.amount <<  "}";
}

std::string Transaction::to_string() {
    std::ostringstream string_stream;
    string_stream << *this;
    return string_stream.str();
}

void Transaction::set_current_date() {
    this->date = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

const std::string &Transaction::getHash() const {
    return this->hash;
}

void Transaction::setHash(const std::string &hash) {
    this->hash = hash;
}

const std::string &Transaction::getPreviousHash() const {
    return this->previous_hash;
}

void Transaction::setPreviousHash(const std::string &previousHash) {
    this->previous_hash = previousHash;
}

double Transaction::getAmount() const {
    return this->amount;
}

void Transaction::setAmount(double amount) {
    this->amount = amount;
}

bool Transaction::operator==(const Transaction &rhs) const {
    return from == rhs.from &&
            this->to == rhs.to &&
            this->type == rhs.type &&
            this->date == rhs.date &&
            this->extra_data == rhs.extra_data &&
            this->hash == rhs.hash &&
            this->previous_hash == rhs.previous_hash &&
            this->amount == rhs.amount;
}

bool Transaction::operator!=(const Transaction &rhs) const {
    return !(rhs == *this);
}

Transaction::Transaction(const std::string &from, const std::string &to, uint64_t type,
                         const std::map<std::string, std::string> &extraData, const std::string &previousHash,
                         double amount) : from(from), to(to), type(type), extra_data(extraData),
                                            previous_hash(previousHash), amount(amount) {
    this->from = from;
    this->to = to;
    this->type = type;
    this->extra_data = extraData;
    this->previous_hash = previousHash;
    this->amount = amount;
}

Transaction::Transaction(const std::string &from, const std::string &to, uint64_t type, uint64_t date,
                         const std::map<std::string, std::string> &extraData, const std::string &previousHash,
                         double amount) : from(from), to(to), type(type), date(date), extra_data(extraData),
                                            previous_hash(previousHash), amount(amount) {
    this->from = from;
    this->to = to;
    this->type = type;
    this->date = date;
    this->extra_data = extraData;
    this->previous_hash = previousHash;
    this->amount = amount;
}

Transaction::Transaction(const std::string &from, const std::string &to, uint64_t type, uint64_t date,
                         const std::map<std::string, std::string> &extraData, const std::string &hash,
                         const std::string &previousHash, double amount) : from(from), to(to), type(type), date(date),
                                                                             extra_data(extraData), hash(hash),
                                                                             previous_hash(previousHash),
                                                                             amount(amount) {
    this->from = from;
    this->to = to;
    this->type = type;
    this->date = date;
    this->extra_data = extraData;
    this->hash = hash;
    this->previous_hash = previousHash;
    this->amount = amount;
}

double Transaction::getFee() const {
    return this->fee;
}

void Transaction::setFee(double fee) {
    this->fee = fee;
}
