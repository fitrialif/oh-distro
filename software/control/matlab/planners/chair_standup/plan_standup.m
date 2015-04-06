function [qtraj,supports,support_times] = plan_standup(r,x0,speed,stand_from_squat_flag)

  if nargin < 4
    stand_from_squat_flag = 0;
  end

nq = r.getNumPositions();
np = nq;
q0 = x0(1:nq);

%% Add in the appropriate path
path = [getenv('DRC_BASE'),'/software/control/matlab/planners/prone'];
addpath(path);

load([getenv('DRC_BASE'),'/software/control/matlab/planners/chair_standup/chair_standup_data.mat'])


% robot = robot.removeCollisionGroupsExcept({});
data_struct = {};
kpt = KinematicPoseTrajectory(r,{});
kpt = kpt.useRobotiqHands();
kpt = kpt.addTerrain();
[~,kpt] = kpt.addCollisionGeometryToRobot();



%% Torque Constraint
joint_names = kpt.robot.getPositionFrame.coordinates;
idx_arm = ~cellfun('isempty',strfind(joint_names,'arm'));
% idx_back = ~cellfun('isempty',strfind(joint_names,'back'));
% idx = or(idx_arm,idx_back);
idx = idx_arm;
names_arm_back = joint_names(idx);
pmin = Point(kpt.robot.getInputFrame,r.umin*0.4);
pmax = Point(kpt.robot.getInputFrame,r.umax*0.4);


lb = zeros(length(names_arm_back),1);
ub = lb;
joint_idx = zeros(length(names_arm_back),1);


for j = 1:length(joint_idx)
  name = names_arm_back{j};
  joint_idx(j) = kpt.robot.findPositionIndices(name);
  lb(j) = pmin.([name,'_motor']);
  ub(j) = pmax.([name,'_motor']);
end

torque_constraint = GravityCompensationTorqueConstraint(kpt.robot,joint_idx,lb,ub);
constraints = {torque_constraint};

%% Nominal pose
atlas_fp = load([getenv('DRC_BASE'),'/software/control/matlab/data/atlas_v4_fp.mat']);
xstar = atlas_fp.xstar;
qstar = xstar(1:nq);
arm_idx = kpt.robot.findPositionIndices('arm');


%% Sitting with COM over feet
seat_data = load('data_sitting.mat');
clear options;
contacts = {'l_foot','r_foot','r_fpelvis','l_fpelvis'};
options.constraints = constraints;

options.enforce_collision = 0;
options.enforce_contact = 0;
options.enforce_quasistatic = 1;
kpt.shrink_factor = 0.5;
options.no_movement.contacts = contacts;
options.no_movement.q = q0;
kpt.shrink_factor = 0.5;

q_nom = q_sol(:,2);
q_nom(1:6) = q0(1:6);

% q_nom(arm_idx) = qstar(arm_idx);
options.qs_contacts = {'l_foot','r_foot'};
[q,F,info,infeasible_constraint,ik] = kpt.findPose(contacts,{},q_nom,options);
info
infeasible_constraint
kpt.drawCOM(r,q);
q_1 = q;

%% Standing in nominal pose
options_old = options;
clear options;
contacts = {'l_foot','r_foot'};
options.no_movement.contacts = contacts;
options.no_movement.q = q_1;
options.enforce_collision = 0;
options.enforce_contacts = 0;
options.enforce_quasistatic = 1;
atlas_fp = load([getenv('DRC_BASE'),'/software/control/matlab/data/atlas_v4_fp.mat']);
q_nom = atlas_fp.xstar(1:nq);
q_nom(1:6) = q_1(1:6);
[q,F,info,infeasible_constraint,ik] = kpt.findPose(contacts,{},q_nom,options);
info
infeasible_constraint
kpt.drawCOM(r,q);
q_2 = q;


% now we want to rescale the trajectory
max_degrees_per_second = 15;
max_base_meters_per_second = 0.05;
joint_v_max = repmat(max_degrees_per_second*pi/180, r.getNumVelocities()-3, 1);
joint_v_max = speed*3/2*joint_v_max;
xyz_v_max = repmat(max_base_meters_per_second,3,1);
qd_max = [xyz_v_max;joint_v_max];

qtraj_1 = kpt.constructTrajectory([q0,q_1]);
qtraj_2 = kpt.constructTrajectory([q_1,q_2]);

qtraj_1 = rescalePlanTiming(qtraj_1,qd_max);
qtraj_2 = rescalePlanTiming(qtraj_2,qd_max);
qtraj_2 = qtraj_2.shiftTime(qtraj_1.tspan(2));
qtraj = qtraj_1.append(qtraj_2);

t0 = qtraj_1.tspan(1);
t1 = qtraj_1.tspan(2);
tf = qtraj.tspan(2);
support_times = [t0,t1,tf];

supports = struct('bodies',{},'contact_pts',{});
supports(1).bodies = [r.findLinkId('l_foot'),r.findLinkId('r_foot'),r.findLinkId('pelvis'),r.findLinkId('pelvis')];
supports(1).contact_pts = {kpt.c('l_foot'),kpt.c('r_foot'),kpt.c('l_fpelvis'),kpt.c('r_fpelvis')};

supports(2).bodies = [r.findLinkId('l_foot'),r.findLinkId('r_foot')];
supports(2).contact_pts = {kpt.c('l_foot'),kpt.c('r_foot')};

supports(3) = supports(2);

if stand_from_squat_flag
  supports(1) = supports(2);
end

end













