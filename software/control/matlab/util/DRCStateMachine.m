classdef DRCStateMachine

  properties (SetAccess=private,GetAccess=public)
    active_controller;
    controllers; 
  end

  methods
    function obj = DRCStateMachine(controllers,active_controller)
      typecheck(controllers,'struct');
      obj.controllers = controllers;
      obj = setActiveController(obj,active_controller);
    end
    
    function obj = addController(obj,name,controller)
      typecheck(name,'char');
      typecheck(controller,'DRCController');
      obj.controllers = setfield(obj.controllers, name, controller);
    end
    
    function obj = setActiveController(obj,active_controller)
      typecheck(active_controller,'char');
      if ~any(strcmp(active_controller,fieldnames(obj.controllers)))
        error(strcmp('DRCStateMachine::Invalid controller name:',active_controller));
      end
      obj.active_controller = active_controller;
    end
    
    function run(obj)
      data = [];
      while 1
        ctrl = getfield(obj.controllers,obj.active_controller);
        msg = ['Initializing controller: ' ctrl.name];
        send_status(3, 0, 0, msg );
        disp(msg);
        
        ctrl = ctrl.initialize(data);
        
        msg = ['Running controller: ' ctrl.name];
        send_status(3, 0, 0, msg );
        disp(msg);
        transition_data = ctrl.run();
        
        fn = fieldnames(transition_data);
        transition_to = fn{1}; % arbitrarily take the first one if multiple transitions occured simultaneously
        
        msg = ['Transitioning from ' ctrl.name ' to ' transition_to];
        send_status(3, 0, 0, msg );
        disp(msg);
        
        obj = setActiveController(obj,transition_to);
        data = getfield(transition_data,obj.active_controller);
      end
    end
  end
  
end