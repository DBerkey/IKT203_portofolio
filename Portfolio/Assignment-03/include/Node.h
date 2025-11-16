//
// Created by abden on 14.11.2025.
//

#ifndef IKT203_COURSE_ASSIGNMENTS_NODE_H
#define IKT203_COURSE_ASSIGNMENTS_NODE_H
#include <string>


class Node {
    private:
        double *data;
        int height;
        Node *left;
        Node *right;
        std::string key;

    public:
        Node(double data, const std::string &key, Node* left = nullptr, Node* right = nullptr);
        ~Node();

        [[nodiscard]] double GetData() const;
        [[nodiscard]] Node *GetLeft() const;
        [[nodiscard]] Node *GetRight() const;
        [[nodiscard]] const std::string &GetKey() const;
        [[nodiscard]] int GetHeight() const;

        void SetData(double data);
        void SetLeft(Node *node);
        void SetRight(Node *node);
        void SetKey(const std::string &key);
        void SetHeight(int height);
    };



#endif //IKT203_COURSE_ASSIGNMENTS_NODE_H