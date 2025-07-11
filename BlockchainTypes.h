//////////////////
// Transactions //
//////////////////
#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <openssl/rsa.h>

class Transaction {
public:
    std::string sender; // Sender's wallet ID
    std::string receiver; // Receiver's wallet ID
    float amount; // Amount of money transferred
    std::string signature; // Digital signature for this transaction
    int nonce; // Nonce for transaction, can be used for security or versioning
    unsigned int signatureLength; // Length of the digital signature

    // Constructor to initialize the transaction
    Transaction(std::string sender, std::string receiver, float amount, int nonce);

    // Method to sign the transaction with the sender's private key
    void sign(RSA* privateKey);

    // Method to verify the transaction using the sender's public key
    bool verify(RSA* publicKey) const;

    // Method to check overall validity of the transaction
    bool isValid(RSA* publicKey) const;
};

#endif // TRANSACTION_H
///////////////
// Contracts //
///////////////
#ifndef CONTRACT_H
#define CONTRACT_H

#include <string>
#include <openssl/rsa.h>

class Contract {
public:
    std::string sender; // Sender's wallet ID
    std::string receiver; // Receiver's wallet ID

    float amount; // Amount of money transferred for the contract

    std::string signature; // Digital signature for this Contract

    std::string contractTerms; // Terms of the contract

    int nonce; // Nonce for transaction, can be used for security or versioning
    unsigned int signatureLength; // Length of the digital signature

    // Constructor to initialize the transaction
    Contract(std::string sender, std::string receiver, float amount, std::string contractTerms, int nonce);

    // Method to sign the contract with the sender's private key
    void sign(RSA* privateKey);

    // Method to verify the contract using the sender's public key
    bool verify(RSA* publicKey) const;

    // Method to check overall validity of the contract
    bool isValid(RSA* publicKey) const;
};

#endif // CONTRACT_H
/////////////
// Wallets //
/////////////
#ifndef WALLET_H
#define WALLET_H

#include <string>
#include <vector>
#include <openssl/rsa.h>
#include "Transaction.h"

class Wallet {
public:
    Wallet(std::string id); // Constructor with wallet ID
    ~Wallet();  // Destructor to free RSA keys

    // Method to send funds to another wallet
    Transaction sendFunds(Wallet& receiver, float amount);

    // Method to update the balance of this wallet based on blockchain transactions
    void updateBalance(const std::vector<Transaction>& transactions);

    // Method to print wallet details
    void printWalletData() const;

    std::string id; // Wallet ID
    float balance; // Wallet balance
    RSA* publicKey; // Public key of the wallet for verification

private:
    RSA* privateKey;  // Private key for signing transactions
    void generateKeys();  // Method to generate RSA key pair
};

#endif // WALLET_H
///////////
// Block //
///////////
#ifndef BLOCK_H
#define BLOCK_H
#pragma once
#include <string>
#include <vector>
#include <ctime>

class Block {
public:
    std::string prevHash;  // Hash of the previous block
    std::string blockHash; // Hash of the current block
    std::vector<Transaction> transactions; // List of transactions in this block
    std::vector<Contract> contracts; // List of contracts in this block
    std::time_t timestamp; // Timestamp for when this block was created
    int nonce;  // Nonce used for mining
    int difficulty;  // The difficulty level for mining this block

    // Constructor to initialize a block with transactions, previous hash, and difficulty
    Block(std::vector<Transaction> transactions, std::string prevHash, int difficulty);

    // Method to mine the block by finding a nonce that satisfies the difficulty
    std::string mineBlock();

    // Method to generate the hash of the block's contents
    std::string generateHash() const;

    // Utility method to perform SHA-256 hashing
    std::string sha256(const std::string str) const;
};
#endif // BLOCK_H

