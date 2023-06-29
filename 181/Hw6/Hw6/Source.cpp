//Quinton Young hw6
#include <string>
#include <vector>
#include <algorithm>
class PayCoinTransaction {
public:
    std::string senderPublicKey;
    std::string recipientPublicKey;
    std::string amount;
    std::string signature;

    PayCoinTransaction(std::string sender, std::string recipient, std::string amount, std::string signature) {
        this->senderPublicKey = sender;
        this->recipientPublicKey = recipient;
        this->amount = amount;
        this->signature = signature;
    }
};

class Blockchain {
public:
    std::vector<PayCoinTransaction> ledger;

    void addTransaction(PayCoinTransaction transaction) {
        ledger.push_back(transaction);
    }
};
//verifySignature function is assumed to be provided.
bool verifySignature(std::string pubKey, std::string message, std::string signature);

//checks if the new transaction already exists in the ledger and also verifies the signature using the verifySignature function. If both checks pass, the transaction is considered valid.
bool isTransactionValid(PayCoinTransaction newTransaction, Blockchain blockchain) {
    // Check if transaction already exists in the ledger
    auto it = std::find(blockchain.ledger.begin(), blockchain.ledger.end(), newTransaction);
    if (it != blockchain.ledger.end()) {
        // Transaction already exists in the ledger
        return false;
    }

    // Verify signature
    if (!verifySignature(newTransaction.senderPublicKey, newTransaction.amount, newTransaction.signature)) {
        // Invalid signature
        return false;
    }

    // If the transaction doesn't exist in the ledger and the signature is valid, the transaction is valid
    return true;
}
//uses isTransactionValid to validate a new transaction. If the transaction is valid, it is added to the blockchain ledger.
void processTransaction(PayCoinTransaction newTransaction, Blockchain& blockchain) {
    // Validate the transaction
    if (isTransactionValid(newTransaction, blockchain)) {
        // If transaction is valid, add it to the ledger
        blockchain.addTransaction(newTransaction);
    }
}