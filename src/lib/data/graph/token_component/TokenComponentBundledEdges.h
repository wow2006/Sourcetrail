#pragma once

#include "types.h"

#include "TokenComponent.h"

class TokenComponentBundledEdges : public TokenComponent {
public:
  enum Direction { DIRECTION_NONE, DIRECTION_FORWARD, DIRECTION_BACKWARD, DIRECTION_INVALID };

  static Direction opposite(Direction direction);

  TokenComponentBundledEdges();

  ~TokenComponentBundledEdges() override;

  virtual std::shared_ptr<TokenComponent> copy() const;

  int getBundledEdgesCount() const;
  std::set<Id> getBundledEdgesIds() const;

  void addBundledEdgesId(Id id, bool forward);
  void removeBundledEdgesId(Id id);

  Direction getDirection();

private:
  std::map<Id, Direction> m_ids;
  Direction m_direction;
};