#!/usr/bin/env ruby

require 'json'
require 'erb'
require 'fileutils'

class CucumberReportGenerator
  def initialize(json_file = 'cucumber_results.json')
    @json_file = json_file
    @results = load_results
  end

  def generate_report
    puts "?? Generating Professional Cucumber Report..."
    
    template = ERB.new(html_template)
    html_content = template.result(binding)
    
    File.write('professional_cucumber_report.html', html_content)
    puts "??Report generated: professional_cucumber_report.html"
  end

  private

  def load_results
    return [] unless File.exist?(@json_file)
    JSON.parse(File.read(@json_file))
  end

  def total_scenarios
    @results.map { |f| f['elements'] }.flatten.size
  end

  def passed_scenarios
    @results.map { |f| f['elements'] }.flatten.count do |scenario|
      scenario['steps'].all? { |step| step['result']['status'] == 'passed' }
    end
  end

  def failed_scenarios
    total_scenarios - passed_scenarios
  end

  def success_rate
    return 0 if total_scenarios == 0
    (passed_scenarios.to_f / total_scenarios * 100).round(2)
  end

  def html_template
    <<~HTML
      <!DOCTYPE html>
      <html lang="en">
      <head>
          <meta charset="UTF-8">
          <meta name="viewport" content="width=device-width, initial-scale=1.0">
          <title>?? Chinese Chess Cucumber Report</title>
          <link href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/6.0.0/css/all.min.css" rel="stylesheet">
          <script src="https://cdn.jsdelivr.net/npm/chart.js"></script>
          <style>
              /* Professional Cucumber styling */
              body { 
                  font-family: 'Segoe UI', system-ui, sans-serif; 
                  margin: 0; 
                  background: linear-gradient(135deg, #23d160, #00c4a7); 
                  min-height: 100vh; 
              }
              .container { max-width: 1200px; margin: 0 auto; padding: 20px; }
              .header { 
                  background: rgba(255,255,255,0.95); 
                  padding: 30px; 
                  border-radius: 15px; 
                  margin-bottom: 30px; 
                  text-align: center; 
                  backdrop-filter: blur(10px); 
              }
              .stats { 
                  display: grid; 
                  grid-template-columns: repeat(auto-fit, minmax(250px, 1fr)); 
                  gap: 20px; 
                  margin-bottom: 30px; 
              }
              .stat-card { 
                  background: white; 
                  padding: 25px; 
                  border-radius: 15px; 
                  text-align: center; 
                  box-shadow: 0 10px 30px rgba(0,0,0,0.1); 
              }
              .passed { color: #23d160; }
              .failed { color: #ff3860; }
              .total { color: #3273dc; }
              .scenarios { 
                  background: white; 
                  padding: 30px; 
                  border-radius: 15px; 
                  box-shadow: 0 10px 30px rgba(0,0,0,0.1); 
              }
              .scenario { 
                  border-left: 4px solid #23d160; 
                  padding: 15px; 
                  margin: 10px 0; 
                  background: #f8f9fa; 
                  border-radius: 0 8px 8px 0; 
              }
              .scenario.failed { border-left-color: #ff3860; }
              .step { 
                  margin: 5px 0; 
                  padding: 8px; 
                  font-family: 'Courier New', monospace; 
                  font-size: 14px; 
              }
              .step.passed { background: #effaf5; color: #257942; }
              .step.failed { background: #feecf0; color: #cc0f35; }
          </style>
      </head>
      <body>
          <div class="container">
              <div class="header">
                  <h1><i class="fas fa-chess"></i> Chinese Chess Cucumber Report</h1>
                  <p>Generated: <%= Time.now.strftime('%B %d, %Y at %I:%M %p') %></p>
              </div>
              
              <div class="stats">
                  <div class="stat-card">
                      <div class="total"><i class="fas fa-list-check"></i></div>
                      <h2 class="total"><%= total_scenarios %></h2>
                      <p>Total Scenarios</p>
                  </div>
                  <div class="stat-card">
                      <div class="passed"><i class="fas fa-check-circle"></i></div>
                      <h2 class="passed"><%= passed_scenarios %></h2>
                      <p>Passed</p>
                  </div>
                  <div class="stat-card">
                      <div class="failed"><i class="fas fa-times-circle"></i></div>
                      <h2 class="failed"><%= failed_scenarios %></h2>
                      <p>Failed</p>
                  </div>
                  <div class="stat-card">
                      <div><i class="fas fa-percentage"></i></div>
                      <h2><%= success_rate %>%</h2>
                      <p>Success Rate</p>
                  </div>
              </div>
              
              <div class="scenarios">
                  <h2><i class="fas fa-play-circle"></i> Test Scenarios</h2>
                  <% @results.each do |feature| %>
                      <% feature['elements'].each do |scenario| %>
                          <% status = scenario['steps'].all? { |s| s['result']['status'] == 'passed' } ? 'passed' : 'failed' %>
                          <div class="scenario <%= status %>">
                              <h3><%= scenario['name'] %></h3>
                              <% scenario['steps'].each do |step| %>
                                  <div class="step <%= step['result']['status'] %>">
                                      <%= step['keyword'] %><%= step['name'] %>
                                      <span style="float: right;"><%= step['result']['duration'] || 0 %>ms</span>
                                  </div>
                              <% end %>
                          </div>
                      <% end %>
                  <% end %>
              </div>
          </div>
      </body>
      </html>
    HTML
  end
end

# Generate the report
CucumberReportGenerator.new.generate_report
