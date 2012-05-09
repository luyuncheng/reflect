#pragma once
#ifndef JSON_ARCHIVE_HPP_4OX35IUJ
#define JSON_ARCHIVE_HPP_4OX35IUJ

#include "archive.hpp"
#include <deque>
#include <map>
#include <string>
#include <vector>

struct JSONArchive;

struct JSONArchiveNode : ArchiveNode {
	JSONArchiveNode(JSONArchive& archive, ArchiveNode::Type t = ArchiveNode::Empty);
	void write(std::ostream& os) const override { write(os, false, 0); }
	void write(std::ostream& os, bool print_inline, int indent) const;
};

struct JSONArchive : Archive {
	JSONArchive();
	ArchiveNode& root() override;
	const ArchiveNode& root() const override;
	void write(std::ostream& os) const override;
	const ArchiveNode& operator[](const std::string& key) const override;
	ArchiveNode& operator[](const std::string& key) override;
	ArchiveNode* make(ArchiveNode::Type t = ArchiveNode::Empty) override { return make_internal(t); }
	
	const ArchiveNode& empty() const { return *empty_; }
private:
	friend struct JSONArchiveNode;
	JSONArchiveNode* empty_;
	JSONArchiveNode* root_;
	std::deque<JSONArchiveNode> nodes_;
	JSONArchiveNode* make_internal(ArchiveNode::Type t = ArchiveNode::Empty);
};

inline JSONArchiveNode::JSONArchiveNode(JSONArchive& archive, ArchiveNode::Type t) : ArchiveNode(archive, t) {}

#endif /* end of include guard: JSON_ARCHIVE_HPP_4OX35IUJ */
