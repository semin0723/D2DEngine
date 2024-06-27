#pragma once

// CollisionEvents
struct TriggerEnter : public Event<TriggerEnter> {
	EntityId _leftEntityId;
	EntityId _rightEntityId;
	TriggerEnter(EntityId left, EntityId right) : _leftEntityId(left), _rightEntityId(right) {}
};

struct TriggerStay : public Event<TriggerStay> {
	EntityId _leftEntityId;
	EntityId _rightEntityId;
	TriggerStay(EntityId left, EntityId right) : _leftEntityId(left), _rightEntityId(right) {}
};

struct TriggerExit : public Event<TriggerExit> {
	EntityId _leftEntityId;
	EntityId _rightEntityId;
	TriggerExit(EntityId left, EntityId right) : _leftEntityId(left), _rightEntityId(right) {}
};

struct CollisionEnter : public Event<CollisionEnter> {
	EntityId _leftEntityId;
	EntityId _rightEntityId;
	CollisionEnter(EntityId left, EntityId right) : _leftEntityId(left), _rightEntityId(right) {}
};

struct CollisionStay : public Event<CollisionStay> {
	EntityId _leftEntityId;
	EntityId _rightEntityId;
	CollisionStay(EntityId left, EntityId right) : _leftEntityId(left), _rightEntityId(right) {}
};

struct CollisionExit : public Event<CollisionExit> {
	EntityId _leftEntityId;
	EntityId _rightEntityId;
	CollisionExit(EntityId left, EntityId right) : _leftEntityId(left), _rightEntityId(right) {}
};