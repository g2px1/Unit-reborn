//
// Created by Kirill Zhukov on 31.05.2022.
//

#include "BlockHandler.h"
#include "iostream"

BlockHandler::BlockHandler() {}
BlockHandler::~BlockHandler() {}

[[noreturn]] void BlockHandler::generate_block(Block *current, bool *lock) {
    std::cout << "Starting 'block generator'" << std::endl;
    loop: {
        *current = Block(1);
        std::this_thread::sleep_for(std::chrono::milliseconds(5000)); // 1000 millisecond * 5 = 5 seconds
        *lock = true;

        std::optional<std::string> op_block_height = unit::DB::get_block_height();
        std::string block_index = (op_block_height.has_value()) ? op_block_height.value() : R"({"index": 0})";
    //    nlohmann::json block_json = nlohmann::json::parse(block_index);
        boost::json::value block_json = boost::json::parse(block_index);
        uint64_t index = boost::json::value_to<uint64_t>(block_json.at("index")) + 1;
        current->setIndex(index);

        if(index == 1){
            std::map<std::string, std::string> map = {{"name", "unit"}, {"value", "0"}, {"bytecode", "null"}};
            Transaction tx = Transaction("genesis", "g2px1", 0,  map, "0", 350000);
            Transaction tx1 = Transaction("genesis", "teo", 0,  map, "0", 350000);
            Transaction tx2 = Transaction("genesis", "sunaked", 0,  map, "0", 350000);
            Transaction tx3 = Transaction("genesis", "merchant", 0,  map, "0", 350000);
            current->setTransactions({tx, tx1, tx2, tx3});
        }

        if(!current->transactions.empty()) {
            try {
                unit::DB::push_transactions(current);
            } catch (std::exception &e) {
                std::cout << e.what() << std::endl;
            }
        }

        current->generate_hash();
        unit::DB::push_block(*current);
        *lock = false;
        goto loop;
    };
}

[[noreturn]] void BlockHandler::run() {
    std::thread th(BlockHandler::generate_block, &currentblock, &block_lock);
    th.detach();
    std::thread server_th(Server::start_server, &transactions_deque);
    server_th.detach();

    loop: {
        if (this->transactions_deque.empty()) {
            goto loop;
        } else {
            goto push_into_block;
        }
    };

    push_into_block: {
        if(block_lock) goto loop;
        Transaction transaction = Transaction(this->transactions_deque.front());
        try {
            currentblock.push_tx(transaction);
        } catch (std::exception &e) {
            std::cout << e.what() << std::endl;
            goto loop;
        }
        this->transactions_deque.erase(this->transactions_deque.begin());
        goto loop;
    };
}