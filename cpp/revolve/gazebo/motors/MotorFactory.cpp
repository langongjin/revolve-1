/*
 * MotorFactory.cpp
 *
 *  Created on: Mar 16, 2015
 *      Author: elte
 */

#include <revolve/gazebo/motors/MotorFactory.h>
#include <revolve/gazebo/motors/Motors.h>

#include <cstdlib>

namespace gz = gazebo;

namespace revolve {
namespace gazebo {

MotorFactory::MotorFactory(::gazebo::physics::ModelPtr model):
	model_(model)
{}

MotorFactory::~MotorFactory() {}

MotorPtr MotorFactory::getMotor(sdf::ElementPtr motor, const std::string & type, const std::string & partId) {
	MotorPtr motorObj;
	if ("servo" == type) {
		motorObj.reset(new ServoMotor(model_, partId, motor));
	}

	return motorObj;
}

MotorPtr MotorFactory::create(sdf::ElementPtr motor) {
	auto typeParam = motor->GetAttribute("type");
	auto partIdParam = motor->GetAttribute("part_id");

	if (!typeParam || !partIdParam) {
		std::cerr << "Motor is missing required attributes (`type` or `part_id`)." << std::endl;
		throw std::runtime_error("Motor error");
	}

	auto partId = partIdParam->GetAsString();
	auto type = typeParam->GetAsString();
	MotorPtr motorObj = this->getMotor(motor, type, partId);

	if (!motorObj) {
		std::cerr << "Motor type '" << type <<
				"' is unknown." << std::endl;
		throw std::runtime_error("Motor error");
	}

	return motorObj;
}

} /* namespace gazebo */
} /* namespace revolve */
