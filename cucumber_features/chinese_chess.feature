Feature: Chinese Chess Rules Validation
  As a Chinese Chess player
  I want the game to enforce all traditional rules
  So that I can play authentic Chinese Chess

  Background:
    Given a standard Chinese Chess board
    And pieces are in their starting positions

  @General @Legal
  Scenario: General moves within palace
    Given the Red General is at position (1, 5)
    When the General moves to (1, 4)
    Then the move should be legal
    And the General should be at (1, 4)

  @General @Illegal
  Scenario: General cannot move outside palace
    Given the Red General is at position (1, 6)  
    When the General attempts to move to (1, 7)
    Then the move should be rejected
    And an error message should indicate "General cannot leave palace"

  @General @FlyingGeneral
  Scenario: Flying General rule violation
    Given the Red General is at (2, 4)
    And the Black General is at (8, 5)
    When the Red General attempts to move to (2, 5)
    Then the move should be rejected
    And the reason should be "Generals cannot face each other"

  @Guard @Legal
  Scenario: Guard moves diagonally in palace
    Given a Red Guard is at (1, 4)
    When the Guard moves diagonally to (2, 5)
    Then the move should be legal

  @Guard @Illegal  
  Scenario: Guard cannot move straight
    Given a Red Guard is at (2, 5)
    When the Guard attempts to move to (2, 6)
    Then the move should be rejected

  @Rook @Legal
  Scenario: Rook moves along clear path
    Given a Red Rook is at (4, 1)
    And there are no pieces between (4, 1) and (4, 9)
    When the Rook moves to (4, 9)
    Then the move should be legal

  @Rook @Illegal
  Scenario: Rook cannot jump over pieces
    Given a Red Rook is at (4, 1)
    And a Black Soldier is at (4, 5)
    When the Rook attempts to move to (4, 9)
    Then the move should be rejected
    And the reason should be "Cannot jump over pieces"

  @Horse @Legal
  Scenario: Horse moves in L-shape when unblocked
    Given a Red Horse is at (3, 3)
    And position (4, 3) is empty
    When the Horse moves to (5, 4)
    Then the move should be legal

  @Horse @Illegal @Blocking
  Scenario: Horse is blocked by adjacent piece
    Given a Red Horse is at (3, 3)
    And a Black Rook is at (4, 3)
    When the Horse attempts to move to (5, 4)
    Then the move should be rejected
    And the reason should be "Horse leg is blocked"

  @Cannon @Legal @NoScreen
  Scenario: Cannon moves like Rook without capturing
    Given a Red Cannon is at (6, 2)
    And there are no pieces between (6, 2) and (6, 8)
    When the Cannon moves to (6, 8)
    Then the move should be legal

  @Cannon @Legal @WithScreen
  Scenario: Cannon captures with exactly one screen
    Given a Red Cannon is at (6, 2)
    And a Black Soldier is at (6, 5)
    And a Black Guard is at (6, 8)
    When the Cannon captures the Guard at (6, 8)
    Then the move should be legal
    And the Black Guard should be captured

  @Cannon @Illegal @NoScreen
  Scenario: Cannon cannot capture without screen
    Given a Red Cannon is at (6, 2)
    And a Black Guard is at (6, 8)
    And there are no pieces between them
    When the Cannon attempts to capture at (6, 8)
    Then the move should be rejected

  @Elephant @Legal
  Scenario: Elephant moves diagonally within home territory
    Given a Red Elephant is at (3, 3)
    And position (4, 4) is empty
    When the Elephant moves to (5, 5)
    Then the move should be legal

  @Elephant @Illegal @River
  Scenario: Elephant cannot cross the river
    Given a Red Elephant is at (5, 3)
    When the Elephant attempts to move to (7, 5)
    Then the move should be rejected
    And the reason should be "Elephant cannot cross river"

  @Elephant @Illegal @Blocking
  Scenario: Elephant blocked at midpoint
    Given a Red Elephant is at (3, 3)
    And a Black Rook is at (4, 4)
    When the Elephant attempts to move to (5, 5)
    Then the move should be rejected
    And the reason should be "Elephant eye is blocked"

  @Soldier @Legal @BeforeRiver
  Scenario: Soldier moves forward before crossing river
    Given a Red Soldier is at (3, 5)
    When the Soldier moves to (4, 5)
    Then the move should be legal

  @Soldier @Illegal @BeforeRiver
  Scenario: Soldier cannot move sideways before river
    Given a Red Soldier is at (3, 5)
    When the Soldier attempts to move to (3, 4)
    Then the move should be rejected

  @Soldier @Legal @AfterRiver
  Scenario: Soldier can move sideways after crossing river
    Given a Red Soldier is at (6, 5)
    When the Soldier moves to (6, 4)
    Then the move should be legal

  @Soldier @Illegal @Backward
  Scenario: Soldier cannot move backward
    Given a Red Soldier is at (6, 5)
    When the Soldier attempts to move to (5, 5)
    Then the move should be rejected

  @GameEnd @Victory
  Scenario: Game ends when General is captured
    Given a Red Rook is at (5, 5)
    And the Black General is at (5, 8)
    When the Rook captures the Black General
    Then Red should win immediately
    And the game should end

  @GameEnd @Continue
  Scenario: Game continues after capturing other pieces
    Given a Red Rook is at (5, 5)
    And a Black Cannon is at (5, 8)
    When the Rook captures the Black Cannon
    Then the game should continue
    And it should be Black's turn

