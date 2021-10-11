#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetLineWidth(1.5);
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_MULTIPLY);
	ofNoFill();

	this->radius = 150;
	for (float deg = 0; deg < 360; deg += 1.5) {

		auto location = glm::vec2(this->radius * cos(deg * DEG_TO_RAD), this->radius * sin(deg * DEG_TO_RAD));
		this->base_location_list.push_back(location);
	}
}

//--------------------------------------------------------------
void ofApp::update() {

	this->log_list.clear();

	for (int base_x = -165; base_x <= 165; base_x += 330) {

		for (int base_y = -165; base_y <= 165; base_y += 330) {

			for (int i = 0; i < this->base_location_list.size(); i++) {

				vector<glm::vec2> log;
				log.push_back(glm::vec2(this->base_location_list[i] + glm::vec2(base_x, base_y)));
				this->log_list.push_back(log);
			}

			int step = 1;
			for (int i = 0; i < this->log_list.size(); i++) {

				int k = 0;
				while (true) {

					auto deg = ofMap(ofNoise(glm::vec3(this->log_list[i].back() * 0.015, ofGetFrameNum() * 0.006 + k * 0.001)), 0, 1, -180, 180);
					auto next = this->log_list[i].back() + glm::vec2(step * cos(deg * DEG_TO_RAD), step * sin(deg * DEG_TO_RAD));

					if (glm::distance(glm::vec2(base_x, base_y), next) < this->radius) {

						this->log_list[i].push_back(next);
					}
					else {

						break;
					}

					k++;
				}
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5);
	
	for (int i = 0; i < this->log_list.size(); i++) {

		if (this->log_list[i].size() > 1) {

			ofNoFill();
			ofSetColor(190);
			ofBeginShape();
			ofVertices(this->log_list[i]);
			ofEndShape();

			ofFill();
			ofDrawCircle(this->log_list[i].back(), 3);
			ofDrawCircle(this->log_list[i].front(), 3);
		}
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}