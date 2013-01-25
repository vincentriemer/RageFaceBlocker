require 'test_helper'

class RageBlockerControllerTest < ActionController::TestCase
  test "should get blocker" do
    get :blocker
    assert_response :success
  end

end
